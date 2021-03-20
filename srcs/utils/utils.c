/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 08:01:25 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/19 20:12:47 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

float			return_positive(float r1, float r2, float min_t)
{
	if (r1 > MIN && r1 < min_t)
		return (r1);
	else if (r2 > MIN && r2 < min_t)
		return (r2);
	return (min_t);
}

float			return_min_positive(float r1, float r2, float min_t)
{
	if (r1 < r2 && r1 > MIN && r1 < min_t)
		return (r1);
	else if (r2 < r1 && r2 > MIN && r2 < min_t)
		return (r2);
	return (min_t);
}

float			define_what_to_ret(float r1, float r2, float min_t)
{
	if (r1 < MIN && r2 < MIN)
		return (min_t);
	else if (r1 > MIN && r2 > MIN)
		return (return_min_positive(r1, r2, min_t));
	else
		return (return_positive(r1, r2, min_t));
	return (min_t);
}

void			mlx_fill(t_scene *scene)
{
	scene->mlx.init = mlx_init();
	scene->mlx.image = mlx_new_image(scene->mlx.init,
						scene->canvas.width, scene->canvas.height);
	scene->mlx.addr = mlx_get_data_addr(scene->mlx.image, &scene->mlx.bpp,
						&scene->mlx.lsize, &scene->mlx.endian);
	scene->mlx.window = mlx_new_window(scene->mlx.init,
			scene->canvas.width, scene->canvas.height, "miniRT by ffarah");
}

void			my_pixel_put(t_mlx *mlx, int x_pix, int y_pix, int col)
{
	char		*dst;

	dst = mlx->addr + (y_pix * mlx->lsize + x_pix * (mlx->bpp / 8));
	*(unsigned int*)dst = col;
}
