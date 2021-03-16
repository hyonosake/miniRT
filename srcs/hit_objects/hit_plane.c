/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 03:11:38 by alex              #+#    #+#             */
/*   Updated: 2021/03/16 13:53:01 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float			plane_intersection(t_plane *plane, float min_t, t_ray *ray)
{
	t_vector	centers;
	float		dots[2];
	float		ret_val;

	centers = v_sub(&ray->orig, &plane->orig);
	//if (v_dot_product(&ray->dir, &plane->normal) > 0)
	//	v_by_scalar(&plane->normal, -1);
	dots[0] = v_dot_product(&plane->normal, &centers);
	dots[1] = v_dot_product(&ray->dir, &plane->normal);
	if (dots[1] == 0)
		dots[1] = MIN;
	ret_val = dots[0] / dots[1];
	if (ret_val > min_t || ret_val < MIN)
		ret_val = min_t;
	return (ret_val);
}

t_intersect		*init_plane(t_plane *pl, float res, t_ray *ray, t_vector *col)
{
	t_intersect	*ans;

	if (!(ans = (t_intersect *)malloc(sizeof(t_intersect))))
		error_throw(-1);
	ans->res = res;
	ans->type = OBJ_PLANE;
	ans->color = *col;
	ans->p_inter = point_from_vector(&ray->dir, res);
	ans->p_inter = v_sub(&ray->orig, &ans->p_inter);
	ans->to_cam = point_from_vector(&ray->dir, -1);
	ans->normal = pl->normal;
	v_normalize(&ans->normal);
	return (ans);	
}
