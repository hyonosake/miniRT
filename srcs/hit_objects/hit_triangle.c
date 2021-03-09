/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_triangle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 20:22:23 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/09 17:53:02 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

float			triangle_inter(t_trian *tr, t_ray *ray, float min_t)
{
	float		det;
	float		inv_det;
	t_vector	e1;
	t_vector	e2;
	//t_vector	q_inter;
	t_vector	qvec;
	t_vector	tvec;
	t_vector	pvec;
	float		u;
	float		v;
	float		t;
	//t_vector	cam; 

	//printf("he\n");
	e1 = v_sub(&tr->p[0], &tr->p[1]);
	e2 = v_sub(&tr->p[0], &tr->p[2]);
	pvec = v_cross_product(&ray->dir, &e2);
	det = v_dot_product(&e1, &pvec);
	if (det < MIN && det > -MIN)
	{
		//printf("if I\n");
		return (min_t);	
	}
	inv_det = 1 / det;
	tvec = v_sub(&tr->p[0], &ray->orig);
	u = v_dot_product(&tvec, &pvec) * inv_det;
	if (u < 0.0 || u > 1.0)
	{
		//printf("if II\n");
		return (min_t);
	}
	qvec = v_cross_product(&tvec, &e1);
	v = v_dot_product(&ray->dir, &qvec) * inv_det;
	//if (v < 0)
	//	v *= -1;
	if (v < 0.0 || u + v > 1.0)
	{
		//printf("if III\n");
		return (min_t);
	}
	t = v_dot_product(&e2, &qvec) * inv_det;
	//printf("%.2f %.2f %.2f\n", t, u, v);
	if (MAGIC)
	{
		tr->magic_nums.xv = 1 - u - v;
		tr->magic_nums.yv = u;
		tr->magic_nums.zv = v;
		tr->magic_nums.mod = v_dot_product(&tr->magic_nums, &tr->magic_nums);
		//v_normalize(&tr->magic_nums);
		//print_vector(&tr->magic_nums, "magick:");
	}
	//printf("t = %.2f\n", t);
	if (t < min_t && t > MIN)
		return (t);
	return (min_t);
}

t_intersect		*init_trian(t_trian *tr, float res, t_ray *ray, t_vector *col)
{
	t_intersect	*ans;

	if (!(ans = (t_intersect *)malloc(sizeof(t_intersect))))
		error_throw(-1);
	ans->res = res;
	ans->type = OBJ_TRIAN;
	if (MAGIC)
	{
		ans->color = tr->magic_nums;
	}
	else
		ans->color = *col;
	ans->p_inter = point_from_vector(&ray->dir, res);
	ans->p_inter = v_add(&ans->p_inter, &ray->orig);
	ans->to_cam = point_from_vector(&ray->dir, -1);
	ans->normal = tr->normal;
	if (v_dot_product(&ans->normal, &ans->to_cam) < 0)
		v_by_scalar(&ans->normal, -1);
	v_normalize(&ans->normal);
	return (ans);	
}

