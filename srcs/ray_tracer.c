/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 12:33:58 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/01 14:30:15 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
void			ray_transform(t_ray *ray, t_scene *scene, t_basis *b)
{
	double		c[3];

	if (!ray)
		error_throw(-1);
	c[0] = scene->canvas->x_pixel - scene->canvas->width / 2;
	c[1] = scene->canvas->height/ 2 - scene->canvas->y_pixel;
	c[2] = scene->canvas->width / (2 * tan(scene->cameras->fov / 2));
	v_from_basis(b, ray->dir, c);
}		


void			loop_through_pixels(t_scene *scene)
{
	t_ray		*ray;
	t_intersect	*ans;
	//int			col;
	t_basis		*b;

	ray = new_ray(v_from_values(0,0,0), copy_vector(scene->cameras->orig));
	b = basis_init(scene->cameras->dir);
	scene->canvas->x_pixel = 0;
	while(scene->canvas->x_pixel < scene->canvas->width)
	{
		scene->canvas->y_pixel = 0;
		while(scene->canvas->y_pixel < scene->canvas->height)
		{
			//printf("[%d %d]\n",scene->canvas->x_pixel, scene->canvas->y_pixel);
			ray_transform(ray, scene, b);
			ans = ray_objects_intersection(scene->objects, ray);
			//col = blinn_phong(ans, scene);
			int col =  blinn_phong(ans, scene);
			mlx_pixel_put(scene->mlx_init, scene->mlx_window, scene->canvas->x_pixel,
								scene->canvas->y_pixel,col);
			scene->canvas->y_pixel++;
		}
		scene->canvas->x_pixel++;
	}
	basis_free(b);
	free_ray(ray);
}