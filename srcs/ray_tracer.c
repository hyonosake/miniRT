/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 12:33:58 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/06 23:20:06 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
void			ray_transform(t_ray *ray, t_scene *scene, t_basis *b)
{
	t_vector	c;
	if (!ray)
		error_throw(-1);
	c.xv = scene->canvas.x_pixel - scene->canvas.width / 2;
	c.yv = scene->canvas.height/ 2 - scene->canvas.y_pixel;
	c.zv = scene->canvas.width / (2 * tan(scene->cameras->fov / 2));
	ray->dir = v_from_basis(b, &c);
	//ray->dir.mod = sqrt(v_dot_product(&ray->dir, &ray->dir));
	v_normalize(&ray->dir);
}		


void			loop_through_pixels(t_scene *scene)
{
	t_ray		ray;
	t_intersect	*ans;
	int			col;
	t_basis		b;

	b = basis_init(&scene->cameras->dir);
	ray = new_ray(&scene->cameras->dir, &scene->cameras->saved_orig);
	scene->canvas.x_pixel = 0;
	while(scene->canvas.x_pixel < scene->canvas.width)
	{
		scene->canvas.y_pixel = 0;
		while(scene->canvas.y_pixel < scene->canvas.height)
		{
			ray_transform(&ray, scene, &b);
			ans = ray_objects_intersection(scene->objects, &ray);
			// float r = (float)(scene->canvas.x_pixel) / (float)(scene->canvas.width);
			// float g = (float)(scene->canvas.y_pixel) / (float)(scene->canvas.height);
			// float b = 0.2;
			// int ir = (int)(255.99 * r);
			// int ig = (int)(255.99 * g);
			// int ib = (int)(255.99 * b);
			// col = ir << 16 | ig << 8 | ib;
			col = blinn_phong(ans, scene);
			mlx_pixel_put(scene->mlx_init, scene->mlx_window, scene->canvas.x_pixel,
						  scene->canvas.y_pixel,col);
			scene->canvas.y_pixel++;
		}
		scene->canvas.x_pixel++;
		free(ans);
	}
}