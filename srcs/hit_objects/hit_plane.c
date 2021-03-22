/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 03:11:38 by alex              #+#    #+#             */
/*   Updated: 2021/03/22 11:18:07 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float			plane_intersection(t_plane *plane, float min_t, t_ray *ray)
{
	t_vector	centers;
	float		dots[2];
	float		ret_val;

	centers = v_sub(&ray->orig, &plane->orig);
	dots[0] = v_dot_product(&plane->normal, &centers);
	if (ft_fabs(dots[0]) < MIN)
		dots[0] = -MIN;
	dots[1] = v_dot_product(&ray->dir, &plane->normal);
	if (dots[1] == 0)
		dots[1] = MIN;
	ret_val = dots[0] / dots[1];
	if (ret_val > min_t || ret_val < MIN)
		ret_val = min_t;
	return (ret_val);
}
