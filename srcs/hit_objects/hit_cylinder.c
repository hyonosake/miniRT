/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 09:22:18 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/16 23:46:33 by ffarah           ###   ########.fr       */
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

float			correct_solution(t_cylinder *cy, float min_t, t_ray *ray)
{
	float		dots[2];
	t_vector	ap;
	
	ap = point_from_vector(&ray->dir, cy->t[0]);
	ap = v_sub(&cy->orig, &ap);
	dots[0] = ft_fabs(v_dot_product(&cy->axis, &ap));
	ap = point_from_vector(&ray->dir, cy->t[1]);
	ap = v_sub(&cy->orig, &ap);
	dots[1] = ft_fabs(v_dot_product(&cy->axis, &ap));
	if (dots[0] > cy->lhalf)
		cy->t[0] = -1;
	if (dots[1] > cy->lhalf)
		cy->t[1] = -1;
	return (return_min_positive(cy->t[0], cy->t[1], min_t));
}

float			cylinder_intersection(t_cylinder *cy, t_ray *ray, float min_t)
{
	float		a;
	float		b;
	float		c;
	float		ret_val;
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
	//printf("t: [%.2f %.2f] ? %.2f\t", cy->t[0], cy->t[1], min_t);
	//if ((cy->t[0] > MIN && cy->t[1] < -MIN) || (cy->t[1] > MIN && cy->t[0] < -MIN))
	//{
	//	printf("qq! [%.2f %.2f]\n", cy->t[0], cy->t[1]);
	//	cy->is_inside = 1;
	//}
	if ((cy->t[0] < MIN && cy->t[1] < MIN) ||
		(cy->t[0] > min_t && cy->t[1] > min_t))
		return (min_t);
	ret_val = correct_solution(cy, min_t, ray);
	if (ret_val < min_t)
		cy->norm = create_normal(cy, ret_val, ray);
	//printf("and i ret %.2f\n", ret_val);
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
	ans->p_inter = v_sub(&ray->orig, &ans->p_inter);
	//print_vector(&ans->p_inter, "inter p");
	ans->normal = ((t_cylinder *)cy->content)->norm;
	v_normalize(&ans->normal);
	ans->to_cam = point_from_vector(&ray->dir, -1);
	ans->type = cy->type;
	return (ans);
}