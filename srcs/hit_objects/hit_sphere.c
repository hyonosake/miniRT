/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 03:10:18 by alex              #+#    #+#             */
/*   Updated: 2021/03/17 08:32:19 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float			sphere_intersection(t_sphere *sp, t_ray *ray, float min_t)
{
	float		coeffs[3];
	float		det;
	float		t[2];
	t_vector	centers;

	centers = v_sub(&ray->orig, &sp->orig);
	coeffs[1] = -2 * v_dot_product(&centers, &ray->dir);
	coeffs[2] = v_dot_product(&centers, &centers) - sp->rsq;
	det = coeffs[1] * coeffs[1] - 4 * coeffs[2];
	if (det < 0)
		return (min_t);
	t[0] = (-coeffs[1] + sqrt(det)) * 0.5;
	t[1] = (-coeffs[1] - sqrt(det)) * 0.5;
	//float ret_val = min_t;
	//if (t[0] < MIN && t[1] < MIN)
	//	ret_val = min_t;
	//else if (t[0] > MIN && t[1] > MIN)
	//	ret_val = return_min_positive(t[0], t[1], min_t);
	//else
	//	ret_val = return_positive(t[0], t[1], min_t);
	//return (ret_val);
	return (define_what_to_ret(t[0], t[1], min_t));
}

t_intersect		*init_sphere(t_object *sphere, float res, t_ray *ray)
{
	t_intersect	*ans;

	if (!(ans = (t_intersect *)malloc(sizeof(t_intersect))))
		error_throw(-1);
	ans->color = sphere->color;
	ans->res = res;
	ans->p_inter = point_from_vector(&ray->dir, res);
	ans->normal = v_sub(&((t_sphere *)sphere->content)->orig, &ans->p_inter);
	v_normalize(&ans->normal);
	ans->to_cam = point_from_vector(&ray->dir, -1);
	ans->type = sphere->type;
	return (ans);
}