/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_disk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 08:16:39 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/12 14:45:45 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"


float			disk_intersection(t_disk *disk, t_ray *ray, float min_t)
{
	float		res;
	t_vector	ap;
	t_vector	p_inter;
	print_vector(&disk->orig, "disk origin:");
	if ((res = plane_intersection((t_plane *)disk, min_t, ray)) < min_t)
	{
		p_inter = point_from_vector(&ray->dir, res);
		ap = v_sub(&disk->orig, &p_inter);
		if (ap.mod < disk->radius)
			return (res);
		return (min_t);
	}
	return (min_t);		
}