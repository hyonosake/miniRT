/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_square.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 03:14:03 by alex              #+#    #+#             */
/*   Updated: 2021/03/22 11:50:36 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int				square_intersection(t_square *sq, t_ray *ray, float res)
{
	t_vector	a_p;
	float		dot;

	a_p = point_from_vector(&ray->dir, res * (1 - MIN));
	a_p = v_sub(&sq->orig, &a_p);
	dot = ft_fabs(v_dot_product(&a_p, &sq->b_sq.j));
	if (dot <= sq->ahalf)
	{
		dot = ft_fabs(v_dot_product(&a_p, &sq->b_sq.i));
		if (dot <= sq->ahalf)
			return (1);
	}
	return (0);
}
