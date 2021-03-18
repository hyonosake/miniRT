/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 16:08:01 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/18 16:10:26 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int			col_to_int(t_vector *coeffs, float to_cam)
{
	int		rgb[3];
	int		i;

	if (to_cam > 1)
		to_cam = 1;
	else if (to_cam < 0.2)
		to_cam = 0.2;
	i = 0;
	rgb[0] = coeffs->xv * 255 * to_cam;
	rgb[1] = coeffs->yv * 255 * to_cam;
	rgb[2] = coeffs->zv * 255 * to_cam;
	while (i < 3)
	{
		if (rgb[i] > 255)
			rgb[i] = 255;
		++i;
	}
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}
