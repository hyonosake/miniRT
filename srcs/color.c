/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 20:33:38 by alex              #+#    #+#             */
/*   Updated: 2021/03/03 15:07:54 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vector		color_create(int r, int g, int b)
{
	t_vector	new;

	// if (!(new = (t_color *)malloc(sizeof(t_color))))
	// 	error_throw(-1);
	if (r > 255 || r < 0 || g > 255 || g < 0 ||
		b > 255 || b < 0)
		error_throw(-2);
	new.xv = r * VECTORIZE_COLOR;
	new.yv = g * VECTORIZE_COLOR;
	new.zv = b * VECTORIZE_COLOR;
	return (new);
}
