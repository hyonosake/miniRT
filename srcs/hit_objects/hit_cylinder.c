/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 22:13:30 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/14 16:41:05 by alex             ###   ########.fr       */
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
	float		v[2];
	t_vector	co;
	t_vector	cp;
	//a = v_dot_product(&ray->dir, &ray->dir) *
	// print_vector(&cy->orig, "cy");
	co = v_sub(&cy->orig, &ray->orig);
	a = v_dot_product(&ray->dir, &cy->axis) * v_dot_product(&ray->dir, &cy->axis) - 1;
	b = 2 * (v_dot_product(&co, &cy->axis) * v_dot_product(&ray->dir, & cy->axis) -
			v_dot_product(&ray->dir, &co));
	c = v_dot_product(&co, &cy->axis) * v_dot_product(&co, &cy->axis) + cy->rsq - co.mod * co.mod; //???
	det = b * b - 4 * a * c;
	if (det < 0)
		return (min_t);
	t1 = (- b + sqrt(det) ) / (2 * a);
	t2 = (- b - sqrt(det) ) / (2 * a);
	if (ray->dir.xv == 0 && ray->dir.yv == 0 && ray->dir.zv == -1)
	{
		printf("once in a lifetime\n");
		print_vector(&ray->dir, "r_d");
		print_vector(&cy->axis, "axiss");
		print_vector(&co, "CO");
		printf("r = %.2f = %.2f\n", cy->r, cy->rsq);
		printf("det = %.2f\n", det);
		printf("ray->dir * cy->axis = %.2f\n", v_dot_product(&ray->dir, &cy->axis));
		printf("a = %.2f\nb = %.2f\nc = %.2f\n", a, b, c);
		printf("[%.2f %.3f]\n", t1, t2);
	}
	// if (t1 < t2 && t1 > MIN)
	// 	return (t1);
	cp = point_from_vector(&ray->dir, t1);
	v_by_scalar(&cp, -1);
	cp = v_sub(&co, &cp);
	float dot = v_dot_product(&cy->axis, &cp);
	if (ft_fabs(dot) < cy->len * 0.5)
		v[0] = t1;
	else
		v[0] = min_t;
	cp = point_from_vector(&ray->dir, t2);
	v_by_scalar(&cp, -1);
	cp = v_sub(&co, &cp);
	dot = v_dot_product(&cy->axis, &cp);
	if (ft_fabs(dot) < cy->len * 0.5)
		v[1] = t2;
	else
		v[1] = min_t;
	
	if (v[0] > v[1] && v[0] > MIN)
		return (v[0]);
	else if (v[1] > v[0] && v[1] > MIN)
		return (v[1]);
	// else if (t2 < t1 && t2 > MIN)
	// 	return (t2);
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