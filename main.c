/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 22:07:12 by alex              #+#    #+#             */
/*   Updated: 2021/02/18 17:22:17 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"
#include <stdio.h>

int 				col_to_int(t_color *color, double *intens)
{
	int				r[3];
	int				i;
	int				res;
	i = 0;
	r[0] = color->r * intens[0];
	r[1] = color->g * intens[1];
	r[2] = color->b * intens[2];
	while (i < 2)
	{
		if (r[i] > 255)
			r[i] = 255;
		i++;
	}
	res = r[0] << 16 | r[1] << 8 | r[2];
	return (res);
}


int					blinn_phong(t_intersect *ans, t_scene *scene)
{
	t_vector		*to_light;
	t_vector		*bisect;
	t_intersect		*shadow;
	t_light			*tmp;
	t_ray			*shadow_ray;
	double			intens[3];
	double			diffuse;
	double			specular;

	if (ans == NULL)
		return (BACKGROUND_COLOR);
	tmp = scene->lights;
	intens[0] = scene->ambient->color->r/255 * scene->ambient->intensity;
	intens[1] = scene->ambient->color->g/255 * scene->ambient->intensity;
	intens[2] = scene->ambient->color->b/255 * scene->ambient->intensity;
	while (tmp)
	{
		to_light = v_from_p(ans->p_inter, tmp->orig);
		v_normalize(to_light);
		shadow_ray = new_ray(to_light, ans->p_inter);
		shadow = ray_objects_intersection(scene->objects, shadow_ray);
		if (shadow)
		{
			tmp = tmp->next;
			continue ;
		}
		diffuse = v_dot_product(ans->normal, to_light);
		if (diffuse < 0)
			diffuse = 0;
		specular = v_dot_product(ans->normal, bisect);
		if (specular < 0)
			specular = 0;
		intens[0] += tmp->color->r/255 * pow(diffuse,2) * tmp->intensity;
		intens[1] += tmp->color->g/255 * pow(diffuse,2) * tmp->intensity;
		intens[2] += tmp->color->b/255 * pow(diffuse,2) * tmp->intensity;
		tmp = tmp->next;
	}
	return (col_to_int(ans->color, intens));
}


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
			c[2] = scene->canvas->width / (2 * tan(scene->cameras->fov / 2));
			ray = new_ray(v_from_values(c[0],c[1], c[2]), p_from_values(0, 0, 0));
			v_normalize(ray->dir);
			ans = ray_objects_intersection(scene->objects, ray);
			col = blinn_phong(ans, scene);
			mlx_pixel_put(scene->mlx, scene->window, x_pix, y_pix, col);
			free(ray->dir);
			free(ray->orig);
			free(ray);
			y_pix++;
		}
		x_pix++;
	}
}

void	parse_input(t_scene *scene, int ac, char **av)
{
	char *line;
	int res;
	int	i;
	int fd;
	
	fd = open(av[1], O_RDONLY);
	i = 0;
	if (ac == 3)
		//parse save
		;
	if (ac < 2 || ac > 3)
		error_throw(-2);
	while (av[1][i] != '.' && av[1][i])
		i++;
	if (!av[1][i] || (av[1][i+1] != 'r' && av[1][i+2] != 't') || fd < 0)
		error_throw(-3);
	while((res = get_next_line(fd, &line)) > 0)
	{
		parse_line(line, scene);
		free(line);
	}
}

int			main(int ac, char **av)
{
	t_scene	*scene;
	scene = define_scene();
	t_basis	*c_matrix;
	parse_input(scene, ac, av);
	print_scene(scene);
	t_camera *tmp;
	tmp = scene->cameras;
	transform_scene(scene, tmp);
	print_scene(scene);
	scene->mlx = mlx_init();
	scene->window = mlx_new_window(scene->mlx, scene->canvas->width, scene->canvas->height, "tracer");
	loop_through_pixels(scene, tmp);
	mlx_loop(scene->mlx);
	return (0);
}