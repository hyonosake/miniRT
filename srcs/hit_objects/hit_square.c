/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_square.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 03:14:03 by alex              #+#    #+#             */
/*   Updated: 2021/03/20 02:48:27 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int				square_intersection(t_square *sq, t_ray *ray, float res)
{
	t_basis		b;
	t_vector	a_p;
	float		dot;

	b = basis_init(&sq->normal);
	basis_normalize(&b);
	a_p = point_from_vector(&ray->dir, res);
	a_p = v_sub(&sq->orig, &a_p);
	dot = ft_fabs(v_dot_product(&a_p, &b.j));
	if (dot <= sq->ahalf)
	{
		dot = ft_fabs(v_dot_product(&a_p, &b.i));
		if (dot <= sq->ahalf)
			return (1);
	}
	return (0);
}
