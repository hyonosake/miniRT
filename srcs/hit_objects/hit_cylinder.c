/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 09:22:18 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/15 16:18:59 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_vector		create_normal(t_cylinder *cy, float res, t_ray *ray)
{
	t_vector	tau;
	t_vector	ap;
	t_vector	op;

	op = point_from_vector(&ray->dir, res);
	op = v_sub(&ray->orig, &op);
	ap = v_sub(&cy->orig, &op);
	v_normalize(&ap);
	tau = v_cross_product(&cy->axis, &ap);
	return(v_cross_product(&cy->axis, &tau));
}


float			check_cylinder_output(t_cylinder *cy,float min_t, t_ray *ray)
{
	float		dots[2];
	t_vector	ap;
	float		ret_val;
	//check for t1 first
	ret_val = min_t;
	if (cy->t[0] < MIN)
		cy->t[0] = -MIN;
	if (cy->t[1] < MIN)
		cy->t[1] = -MIN;
	ap = point_from_vector(&ray->dir, cy->t[0]);
	ap = v_sub(&cy->orig, &ap);
	dots[0] = ft_fabs(v_dot_product(&cy->axis, &ap));
	if (dots[0] > cy->len * 0.5)
		dots[0] = -1;
	else if (dots[0] < MIN)
		dots[0] = MIN;
	ap = point_from_vector(&ray->dir, cy->t[1]);
	ap = v_sub(&cy->orig, &ap);
	dots[1] = ft_fabs(v_dot_product(&cy->axis, &ap));
	//if (ray->dir.xv == 0 && ray->dir.yv == 0 && ray->dir.zv == 1)	
		//printf("dots %.2f %.2f\n", dots[0], dots[1]);
	if (dots[1] > cy->len * 0.5)
		dots[1] = -1;
	if (dots[0] < 0 && dots[1] < 0)
		return (min_t);
	if (dots[0] < 0)
		cy->t[0] = -1;
	if (dots[1] < 0)
		cy->t[1] = -1;
	//printf("pair of dots:[%.2f %.2f]\npair of nums: [%.2f %.2f]\n", dots[0], dots[1],
	//																cy->t[0], cy->t[1]);
	return (return_min_positive(cy->t[0], cy->t[1], min_t));
}



float			cylinder_intersection(t_cylinder *cy, t_ray *ray, float min_t)
{
	float		a;
	float		b;
	float		c;
	float ret_val;
	float		det;
	t_vector	co;

	co = v_sub(&cy->orig, &ray->orig);
	a = v_dot_product(&ray->dir, &cy->axis) * v_dot_product(&ray->dir, &cy->axis) - 1;
	b = 2 * (v_dot_product(&co, &cy->axis) * v_dot_product(&ray->dir, & cy->axis) -
			v_dot_product(&ray->dir, &co));
	c = v_dot_product(&co, &cy->axis) * v_dot_product(&co, &cy->axis) + cy->rsq - co.mod * co.mod; //???
	det = b * b - 4 * a * c;
	if (det < 0)
		return (min_t);
	cy->t[0] = (- b + sqrt(det) ) / (2 * a);
	cy->t[1] = (- b - sqrt(det) ) / (2 * a);
	// if (ray->dir.xv == 0 && ray->dir.yv == 0 && ray->dir.zv == 1)	
	// 	printf("%.2f %.2f\n", cy->t[0], cy->t[1]);
	if (cy->t[0] > -MIN && cy->t[0] < MIN)
		cy->t[0] = -1;
	if (cy->t[1] > -MIN && cy->t[1] < MIN)
		cy->t[1] = -1;
	if (cy->t[0] < 0 && cy->t[1] < 0)
		return (min_t);
	ret_val = check_cylinder_output(cy,min_t, ray);
	//printf("I should ret %.2f\n", ret_val);
	if (ret_val < min_t)
		cy->norm = create_normal(cy, ret_val, ray);
	return (ret_val);
}


t_intersect		*init_cylinder(t_object *cy, float res, t_ray *ray)
{
	t_intersect	*ans;

	if (!(ans = (t_intersect *)malloc(sizeof(t_intersect))))
		error_throw(-1);
	ans->color = cy->color;
	ans->res = res;
	ans->p_inter = point_from_vector(&ray->dir, res);
	ans->normal = ((t_cylinder *)cy->content)->norm;
	v_normalize(&ans->normal);
	if (cy->type == INSIDE_OBJ)
	{
		cy->type = OBJ_CYL;
		v_by_scalar(&ans->normal, -1);
	}
	ans->to_cam = point_from_vector(&ray->dir, -1);
	ans->type = cy->type;
	return (ans);
}