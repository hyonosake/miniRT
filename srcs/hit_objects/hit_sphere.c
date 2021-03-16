/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 03:10:18 by alex              #+#    #+#             */
/*   Updated: 2021/03/16 15:33:26 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float			return_min_positive(float r1, float r2, float min_t)
{
	//float		ret_val;
	
	if (r1 > MIN && r1 < min_t && (r2 < MIN || r1 <= r2))
		return(r1);
	if (r2 > MIN && r2 < min_t && (r1 < MIN || r2 < r1) )
		return(r2);
	return (min_t);
}

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
	if ((t[0] > MIN && t[1] < -MIN) || (t[1] > MIN && t[0] < -MIN))
		sp->is_inside = 1;
	return (return_min_positive(t[0], t[1], min_t));
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
	if (((t_sphere *)sphere->content)->is_inside)
	{
		((t_sphere *)sphere->content)->is_inside = 0;
		v_by_scalar(&ans->normal, -1);
	}
	ans->to_cam = point_from_vector(&ray->dir, -1);
	ans->type = sphere->type;
	return (ans);
}