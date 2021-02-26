/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 12:33:58 by ffarah            #+#    #+#             */
/*   Updated: 2021/02/26 17:36:50 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void			loop_through_pixels(t_scene *scene, t_camera *current_cam)
{
	t_ray		*ray;
	t_intersect	*ans;
	int			col;
	double 		c[3];
	int			x_pix;
	int			y_pix;
	double		px;
	double		py;

	x_pix = 0;
	px = 0;
	py = 0;
	while(x_pix < scene->canvas->width)
	{
		y_pix = 0;
		while(y_pix < scene->canvas->height)
		{
			c[0] = (x_pix - scene->canvas->width / 2);
			c[1] = (scene->canvas->height/ 2 - y_pix);
			c[2] = scene->canvas->width / (2 * tan(current_cam->fov / 2));
			ray = new_ray(v_from_values(c[0],c[1], c[2]), p_from_values(0, 0, 0));
			v_normalize(ray->dir);
			ans = ray_objects_intersection(scene->objects, ray);
			col = blinn_phong(ans, scene);
			mlx_pixel_put(scene->mlx_init, scene->mlx_window, x_pix, y_pix, col);
			free_ray(ray);
			y_pix++;
		}
		x_pix++;
	}
}