/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_disk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 08:16:39 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/22 11:50:23 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int				disk_intersection(t_disk *disk, t_ray *ray, float res)
{
	t_vector	p_inter;

	p_inter = point_from_vector(&ray->dir, res);
	p_inter = v_add(&p_inter, &ray->orig);
	p_inter = v_sub(&disk->orig, &p_inter);
	if (p_inter.mod < disk->radius)
		return (1);
	return (0);
}
