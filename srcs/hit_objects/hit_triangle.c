/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_triangle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 20:22:23 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/18 16:15:02 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void			turn_triangle_rgb(float g, float b, t_vector *v)
{
	v->xv = 1 - g - b;
	v->yv = g;
	v->zv = b;
	v->mod = v_dot_product(v, v);
}

float			triangle_inter(t_trian *tr, t_ray *ray, float min_t)
{
	float		det;
	float		inv_det;
	t_vector	tmp[5];
	float		coords[3];
	float		t;

	tmp[0] = v_sub(&tr->p[0], &tr->p[1]);
	tmp[1] = v_sub(&tr->p[0], &tr->p[2]);
	tmp[4] = v_cross_product(&ray->dir, &tmp[1]);
	det = v_dot_product(&tmp[0], &tmp[4]);
	if (det < MIN && det > -MIN)
		return (min_t);
	inv_det = 1 / det;
	tmp[3] = v_sub(&tr->p[0], &ray->orig);
	tr->coords[0] = v_dot_product(&tmp[3], &tmp[4]) * inv_det;
	if (tr->coords[0] < 0.0 || tr->coords[0] > 1.0)
		return (min_t);
	tmp[2] = v_cross_product(&tmp[3], &tmp[0]);
	tr->coords[1] = v_dot_product(&ray->dir, &tmp[2]) * inv_det;
	if (coords[1] < 0.0 || tr->coords[0] + tr->coords[1] > 1.0)
		return (min_t);
	t = v_dot_product(&tmp[1], &tmp[2]) * inv_det;
	if (tr->coords[2] < min_t && tr->coords[2] > MIN)
		return (tr->coords[2]);
	return (min_t);
}

t_intersect		*init_trian(t_trian *tr, float res, t_ray *ray, t_vector *col)
{
	t_intersect	*ans;

	if (!(ans = (t_intersect *)malloc(sizeof(t_intersect))))
		error_throw(MALLOC_ERR);
	ans->res = res;
	ans->type = OBJ_TRIAN;
	if (MAGIC)
		turn_triangle_rgb(tr->coords[0], tr->coords[1], col);
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
