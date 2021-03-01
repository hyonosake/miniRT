/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 12:33:58 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/01 21:06:33 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
void			ray_transform(t_ray *ray, t_scene *scene)
{
	double		c[3];

	if (!ray)
		error_throw(-1);
	c[0] = scene->canvas->x_pixel - scene->canvas->width / 2;
	c[1] = scene->canvas->height/ 2 - scene->canvas->y_pixel;
	c[2] = scene->canvas->width / (2 * tan(scene->cameras->fov / 2));
	ray->dir->xv = c[0];
	ray->dir->yv = c[1];
	ray->dir->zv = c[2];
	ray->dir->mod = sqrt(v_dot_product(ray->dir, ray->dir));
	v_normalize(ray->dir);
}		


void			loop_through_pixels(t_scene *scene)
{
	t_ray		*ray;
	t_intersect	*ans;
	int			col;

	ray = new_ray(copy_vector(scene->cameras->dir), copy_vector(scene->cameras->orig));
	scene->canvas->x_pixel = 0;
	while(scene->canvas->x_pixel < scene->canvas->width)
	{
		scene->canvas->y_pixel = 0;
		while(scene->canvas->y_pixel < scene->canvas->height)
		{
			ray_transform(ray, scene);
			//print_vector(ray->dir, "ray dir:");
			ans = ray_objects_intersection(scene->objects, ray);
			col = blinn_phong(ans, scene);
			mlx_pixel_put(scene->mlx_init, scene->mlx_window, scene->canvas->x_pixel,
								scene->canvas->y_pixel,col);
			scene->canvas->y_pixel++;
		}
		scene->canvas->x_pixel++;
	}
	//basis_free(b);
	free_ray(ray);
}