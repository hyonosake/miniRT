/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_square.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 03:14:03 by alex              #+#    #+#             */
/*   Updated: 2021/03/15 09:21:26 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float			square_intersection(t_square *sq, t_ray *ray, float min_t)
{
	t_basis		b;
	t_vector	a_p;
	float		res;
	float		dot;

	if ((res = plane_intersection((t_plane *)sq, min_t, ray)) < min_t)
	{
		b = basis_init(&sq->normal);
		basis_normalize(&b);
		a_p = point_from_vector(&ray->dir, res);
		a_p = v_sub(&sq->orig, &a_p);
		dot = v_dot_product(&a_p, &b.j);
		if (dot >= -sq->a / 2 && dot <= sq->a / 2)
		{
			dot = v_dot_product(&a_p, &b.i);
			if (dot >= -sq->a / 2 && dot <= sq->a / 2)
				return (res);
		}
	}
	return (min_t);
}