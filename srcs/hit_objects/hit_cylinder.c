/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 22:13:30 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/11 23:30:35 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

float			cylinder_intersection(t_cylinder *cy, t_ray *ray, float min_t)
{
	float		a;
	float		b;
	float		c;
	float		det;
	float		t1;
	float		t2;
	t_vector	co;
	//a = v_dot_product(&ray->dir, &ray->dir) * 
	co = v_sub(&cy->orig, &ray->orig);
	a = v_dot_product(&ray->dir, &cy->axis) * v_dot_product(&ray->dir, &cy->axis) - 1;
	b = 2 * (v_dot_product(&co, & cy->axis) * v_dot_product(&ray->dir, & cy->axis) -
			v_dot_product(&ray->dir, &co));
	c = v_dot_product(&co, &cy->axis) * v_dot_product(&co, &cy->axis) + cy->rsq - co.mod;
	det = b * b - 4 * a * c;
	if (det < 0)
		return (min_t);
	t1 = (- b + sqrt(det) ) / (0.5 * a);
	t2 = (- b - sqrt(det) ) / (0.5 * a);
	printf("[%.2f %.3f]\n", t1, t2);
	if (t1 < t2 && t1 > MIN)
		return (t1);
	else if (t2 < t1 && t2 > MIN)
		return (t2);
	return (min_t);
}


t_intersect		*init_cylinder(t_object *cy, float res, t_ray *ray)
{
	t_intersect	*ans;

	if (!(ans = (t_intersect *)malloc(sizeof(t_intersect))))
		error_throw(-1);
	ans->color = cy->color;
	ans->res = res;
	ans->p_inter = point_from_vector(&ray->dir, res);
	ans->normal = v_sub(&((t_cylinder *)cy->content)->orig, &ans->p_inter);
	if (cy->type == INSIDE_OBJ)
	{
		cy->type = OBJ_CYL;
		v_by_scalar(&ans->normal, -1);
	}
	ans->to_cam = point_from_vector(&ray->dir, -1);
	ans->type = cy->type;
	return (ans);
}