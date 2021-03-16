/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 12:33:58 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/16 13:45:01 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
void			ray_transform(t_ray *ray, t_scene *scene, t_basis *b)
{
	t_vector	c;
	if (!ray)
		error_throw(-1);
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
	t_basis		b;

	b = basis_init(&scene->cameras->dir);
	ray = new_ray(&scene->cameras->dir, &scene->cameras->orig);
	scene->canvas.x_pixel = 0;
	while(scene->canvas.x_pixel < scene->canvas.width)
	{
		scene->canvas.y_pixel = 0;
		while(scene->canvas.y_pixel < scene->canvas.height)
		{
			ray_transform(&ray, scene, &b);
			ans = ray_objects_intersection(scene->objects, &ray);
			col = blinn_phong(ans, scene);
			//if (scene->canvas.x_pixel == scene->canvas.width * 0.5)
			//	printf("y: %d col: %x\n", scene->canvas.y_pixel, ans->int_col);
			my_pixel_put(&scene->mlx, scene->canvas.x_pixel,
			scene->canvas.y_pixel, col);
			//mlx_pixel_put(scene->mlx.init, scene->mlx.window, scene->canvas.x_pixel,
			//				scene->canvas.y_pixel, col);
			scene->canvas.y_pixel++;
		}
		scene->canvas.x_pixel++;
		free(ans);
	}
}