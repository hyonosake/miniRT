/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 03:11:38 by alex              #+#    #+#             */
/*   Updated: 2021/03/03 14:43:51 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

double			plane_intersection(t_plane *plane, double min_t, t_ray *ray)
{
	t_vector	tmp;
	double		coeffs[2];
	double		res;

	tmp = v_sub(&plane->orig, &ray->orig);
	coeffs[0] = v_dot_product(&tmp, &plane->normal);
	//printf("c[0] = %.2f\n", coeffs[0]);
	if (coeffs[0] < 0)
	{
		tmp = point_from_vector(&plane->normal, -1);
		coeffs[0] *= -1;
	}
	else
		tmp = plane->normal;
	coeffs[1] = v_dot_product(&ray->dir, &tmp);
	//printf("c[1] = %.2f\n", coeffs[1]);
	if (coeffs[1] == 0)
		coeffs[1] = MIN;
	res = -coeffs[0] / coeffs[1];
	if (res < min_t && res > MIN) 
		return (res);
	return (min_t);
}

t_intersect		*init_plane(t_plane *pl, double res, t_ray *ray, t_vector *col)
{
	t_intersect	*ans;

	if (!(ans = (t_intersect *)malloc(sizeof(t_intersect))))
		error_throw(-1);
	ans->res = res;
	ans->color = *col;
	ans->p_inter = point_from_vector(&ray->dir, res);
	ans->to_cam = ray->dir;
	v_by_scalar(&ans->to_cam, -1);
	ans->normal = pl->normal;
	v_normalize(&ans->normal);
	// v_normalize(&ans.to_cam);
	return (ans);	
}
