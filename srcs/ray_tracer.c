/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 12:33:58 by ffarah            #+#    #+#             */
/*   Updated: 2021/02/27 02:12:57 by ffarah           ###   ########.fr       */
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

	x_pix = 0;
	//print_scene(scene);
	while(x_pix < scene->canvas->width)
	{
		y_pix = 0;
		while(y_pix < scene->canvas->height)
		{
			c[0] = (x_pix - scene->canvas->width / 2);
			c[1] = (scene->canvas->height/ 2 - y_pix);
			c[2] = scene->canvas->width / (2 * tan(current_cam->fov / 2));
			printf("c[0] = %.2f\n", c[0]);
			ray = (t_ray *)malloc(sizeof(t_ray));
			ray->dir = v_from_values(c[0], c[1], c[2]);
			ray->orig = copy_vector(current_cam->orig);
			v_normalize(ray->dir);
			ans = ray_objects_intersection(scene->objects, ray);
			col = blinn_phong(ans, scene);
			mlx_pixel_put(scene->mlx_init, scene->mlx_window, x_pix, y_pix, col);
			y_pix++;
		}
		x_pix++;
	}
}