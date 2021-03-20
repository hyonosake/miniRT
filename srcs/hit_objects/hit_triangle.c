/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_triangle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 20:22:23 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/19 18:50:20 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

float			triangle_inter(t_trian *tr, t_ray *ray, float min_t)
{
	float		det;
	t_vector	bari[3];

	bari[2] = v_cross_product(&ray->dir, &tr->exc[1]);
	det = v_dot_product(&tr->exc[0], &bari[2]);
	if (det < MIN && det > -MIN)
		return (min_t);
	det = 1 / det;
	bari[1] = v_sub(&tr->p[0], &ray->orig);
	tr->coords[0] = v_dot_product(&bari[1], &bari[2]) * det;
	if (tr->coords[0] < 0.0 || tr->coords[0] > 1.0)
		return (min_t);
	bari[0] = v_cross_product(&bari[1], &tr->exc[0]);
	tr->coords[1] = v_dot_product(&ray->dir, &bari[0]) * det;
	if (tr->coords[1] < 0.0 || tr->coords[0] + tr->coords[1] > 1.0)
		return (min_t);
	tr->coords[2] = v_dot_product(&tr->exc[1], &bari[0]) * det;
	if (tr->coords[2] < min_t && tr->coords[2] > MIN)
		return (tr->coords[2]);
	return (min_t);
}
