/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_square.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 03:14:03 by alex              #+#    #+#             */
/*   Updated: 2021/03/03 14:24:25 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

double			square_intersection(t_square *sq, double min_t, t_ray *ray)
{
	if (sq->a < 0 && ray->dir.mod == 0)
		return (min_t);
	return (min_t);
}