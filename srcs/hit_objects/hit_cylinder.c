/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 09:22:18 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/15 12:54:21 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_vector		create_normal(t_cylinder *cy, float res, t_ray *ray)
{
	t_vector	tau;
	t_vector	ap;
	t_vector	op;

	op = point_from_vector(&ray->dir, res);
	ap = v_sub(&cy->orig, &ray->orig);
	ap = v_sub(&ap, &op);
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
	ap = point_from_vector(&ray->dir, cy->t[0]);
	ap = v_sub(&ray->orig, &ap);
	dots[0] = ft_fabs(v_dot_product(&cy->axis, &ap));
	if (dots[0] > cy->len * 0.5)
		dots[0] = -1;
	else if (dots[0] < MIN)
		dots[0] = MIN;
	ap = point_from_vector(&ray->dir, cy->t[1]);
	ap = v_sub(&ray->orig, &ap);
	dots[1] = ft_fabs(v_dot_product(&cy->axis, &ap));
	if (dots[0] < 0 && dots[1] < 0)
		return (min_t);
	if (dots[1] > cy->len * 0.5)
		dots[1] = -1;
	else if (dots[1] < MIN)
		dots[1] = MIN;
	else if (dots[0] == MIN && dots[1] == MIN && cy->t[0] > MIN && cy->t[0] > 0)
		return (cy->t[0]);
	else if (dots[1] > MIN && dots[0] < 0 && cy->t[1] > MIN && cy->t[1] > 0)
		return (cy->t[1]);
	else
		return (ret_val);
	//else if (dots[0] < 0 && dots[1] < 0)
	//	ret_val = min_t;
	return (ret_val);
}



float			cylinder_intersection(t_cylinder *cy, t_ray *ray, float min_t)
{
	float		a;
	float		b;
	float		c;
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
	float ret_val = min_t;
	//if (ray->dir.xv == 0 && ray->dir.yv == 0 && ray->dir.zv == 1)
	//{
		//printf("once in a lifetime\n");
		//print_vector(&ray->dir, "r_d");
		//print_vector(&cy->axis, "axiss");
		//print_vector(&co, "CO");
		//printf("r = %.2f = %.2f\n", cy->r, cy->rsq);
		//printf("det = %.2f\n", det);
		//printf("ray->dir * cy->axis = %.2f\n", v_dot_product(&ray->dir, &cy->axis));
		//printf("a = %.2f\nb = %.2f\nc = %.2f\n", a, b, c);
		//printf("[%.2f %.3f]\n", cy->t[0], cy->t[1]);
		ret_val = check_cylinder_output(cy, min_t, ray);
		//printf("I shoulda ret %.3f\n", ret_val);
	//}
	if (cy->t[0] < MIN && cy->t[1] < MIN)
		return (min_t);
	if (cy->t[0] < 0)
		cy->t[0] = 0;
	if (cy->t[1] < 0)
		cy->t[1] = 0;
	cy->norm = create_normal(cy, ret_val, ray);
	v_normalize(&cy->norm);
	return (check_cylinder_output(cy, min_t, ray));
	return (return_min_positive(cy->t[0], cy->t[1], min_t));
}


t_intersect		*init_cylinder(t_object *cy, float res, t_ray *ray)
{
	t_intersect	*ans;

	if (!(ans = (t_intersect *)malloc(sizeof(t_intersect))))
		error_throw(-1);
	ans->color = cy->color;
	ans->res = res;
	ans->p_inter = point_from_vector(&ray->dir, res);
	//ans->normal = v_sub(&((t_cylinder *)cy->content)->orig, &ans->p_inter);
	//printf("\n---------------\n");
	//print_vector(&ans->normal, "norm:");
	ans->normal = ((t_cylinder *)cy->content)->norm;
	//print_vector(&ans->normal, "norm:");
	//printf("\n---------------\n");
	if (cy->type == INSIDE_OBJ)
	{
		cy->type = OBJ_CYL;
		v_by_scalar(&ans->normal, -1);
	}
	ans->to_cam = point_from_vector(&ray->dir, -1);
	ans->type = cy->type;
	return (ans);
}