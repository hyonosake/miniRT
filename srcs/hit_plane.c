/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 03:11:38 by alex              #+#    #+#             */
/*   Updated: 2021/02/21 03:12:20 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

double			plane_intersection(t_plane *plane, double min_t, t_ray *ray)
{
	t_vector	*tmp;
	double		coeffs[2];
	double		res;

	tmp = v_from_p(ray->orig, plane->orig);
	coeffs[0] = v_dot_product(tmp, plane->normal);
	free(tmp);
	coeffs[1] = v_dot_product(ray->dir, plane->normal);
	if (!coeffs[1])
		coeffs[1] = 0.000001;
	res = coeffs[0] / coeffs[1];
	if (res < min_t) 
		return (res);
	return (min_t);
}

t_intersect		*init_plane(t_plane *pl, double res, t_ray *ray, t_color *col)
{
	t_intersect	*ans;

	if (!(ans = (t_intersect *)malloc(sizeof(t_intersect))))
		error_throw(-1);
	ans->res = res;
	ans->color = col;
	ans->p_inter = p_from_v(ray->dir, res);
	ans->to_cam = v_by_scalar(ray->dir, -1);
	ans->normal = v_cpy(pl->normal);
	v_normalize(ans->normal);
	v_normalize(ans->to_cam);
	return (ans);	
}
