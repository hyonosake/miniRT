/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 12:33:58 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/24 08:26:23 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void			ray_transform(t_ray *ray, t_scene *scene, t_basis *b)
{
	t_vector	c;

	if (!ray)
		error_throw(MALLOC_ERR);
	c.xv = scene->canvas.x_pixel - scene->canvas.width * 0.5;
	c.yv = scene->canvas.height * 0.5 - scene->canvas.y_pixel;
	c.zv = scene->canvas.width * 0.5 / tan(scene->cameras->fov * 0.5);
	ray->dir = v_from_basis(b, &c);
	ray->dir.mod = sqrt(v_dot_product(&ray->dir, &ray->dir));
	v_normalize(&ray->dir);
}

void			loop_through_pixels(t_scene *scene)
{
	t_ray		ray;
	t_intersect	*ans;
	int			col;

	ray = new_ray(&scene->cameras->dir, &scene->cameras->orig);
	ray.saved_orig = scene->cameras->saved_orig;
	scene->canvas.x_pixel = 0;
	while (scene->canvas.x_pixel < scene->canvas.width)
	{
		scene->canvas.y_pixel = 0;
		while (scene->canvas.y_pixel < scene->canvas.height)
		{
			ray_transform(&ray, scene, &scene->r_basis);
			ans = ray_objects_intersection(scene->objects, &ray, MAX);
			col = blinn_phong(ans, scene);
			my_pixel_put(&scene->mlx, scene->canvas.x_pixel,
			scene->canvas.y_pixel, col);
			free(ans);
			scene->canvas.y_pixel++;
		}
		scene->canvas.x_pixel++;
	}
}
