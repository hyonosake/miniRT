/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_disk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 08:16:39 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/13 00:15:31 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"


float			disk_intersection(t_disk *disk, t_ray *ray, float min_t)
{
	float		res;
	t_vector	ap;
	t_vector	p_inter;
	///print_vector(&disk->orig, "disk origin:");
	if ((res = plane_intersection((t_plane *)disk, min_t, ray)) < min_t)
	{
	if (ray->dir.xv == 0 && ray->dir.yv == 0 && ray->dir.zv == -1)
	{
		printf("once in a lifetime.. But why tho?\n");
		print_vector(&ray->dir, "r_d");
		print_vector(&disk->orig, "disc->orig");
	}
		p_inter = point_from_vector(&ray->dir, res);
		ap = v_sub(&disk->orig, &p_inter);
		if (ap.mod < disk->radius)
			return (res);
		return (min_t);
	}
	return (min_t);		
}