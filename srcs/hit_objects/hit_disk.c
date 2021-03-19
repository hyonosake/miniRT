/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_disk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 08:16:39 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/19 15:21:18 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int				disk_intersection(t_disk *disk, t_ray *ray, float res)
{
	t_vector	ap;
	t_vector	p_inter;

	if (v_dot_product(&disk->normal, &ray->dir) > 0)
		v_by_scalar(&disk->normal, -1);
	p_inter = point_from_vector(&ray->dir, res);
	ap = v_sub(&disk->orig, &p_inter);
	if (ap.mod < disk->radius)
		return (1);
	return (0);
}

t_intersect		*init_disk(t_disk *disk, float res, t_ray *ray, t_vector *col)
{
	t_intersect	*ans;

	if (!(ans = (t_intersect *)malloc(sizeof(t_intersect))))
		error_throw(MALLOC_ERR);
	ans->res = res;
	ans->type = DISK;
	ans->color = *col;
	ans->p_inter = point_from_vector(&ray->dir, res);
	ans->p_inter = v_sub(&ray->orig, &ans->p_inter);
	ans->to_cam = point_from_vector(&ray->dir, -1);
	ans->normal = disk->normal;
	v_normalize(&ans->normal);
	return (ans);
}
