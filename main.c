/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 22:07:12 by alex              #+#    #+#             */
/*   Updated: 2021/02/12 12:29:42 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"
#include <stdio.h>

int					bitshift_multiply(double *col)
{
	int				res;
	int				rgb[3];
	int i;

	i = 0;
	rgb[0] = col[0];
	rgb[1] = col[1];
	rgb[2] = col[2];
	while (i < 3)
	{
		if (rgb[i] > 255)
			rgb[i] = 255;
		i++;
	}
	res =  rgb[0] << 16 | rgb[1] << 8 | rgb[2];
	return (res);
}


int					blinn_phong(t_intersect *ans, t_scene *scene)
{
	t_vector		*l;
	t_light			*tmp;
	// t_vector		*h;
	// double			specular;
	t_intersect		*shad;
	double			rgb[3];
	double			diffuse;
	tmp = scene->lights;
	if (!ans)
		return BACKGROUND_COLOR;
	rgb[0] = scene->ambient->color->r * scene->ambient->intensity / 255 * ans->color->r;
	rgb[1] = scene->ambient->color->g * scene->ambient->intensity / 255 * ans->color->g;
	rgb[2] = scene->ambient->color->b * scene->ambient->intensity / 255 * ans->color->b;
	while (tmp)
	{
		l = v_from_p(tmp->orig, ans->p_inter);
		v_normalize(l);
		
		//need to do smth and free
		// h = v_add(l, ans->to_cam);
		// v_normalize(h);
		t_ray *ray = new_ray(v_cpy(l), p_cpy(ans->p_inter));
		if ((shad = ray_objects_intersection(scene->objects, ray)) == NULL)
		{
			diffuse = v_dot_product(ans->normal, l) * 0.9;
			if (diffuse < 0)
				diffuse = 0;
			// specular = v_dot_product(l, h);
			// if (specular < 0)
			// 	specular = 0;
			rgb[0] += (tmp->color->r * tmp->intensity / 255) * diffuse * ans->color->r;
			rgb[1] += (tmp->color->g * tmp->intensity / 255) * diffuse * ans->color->g;
			rgb[2] += (tmp->color->b * tmp->intensity / 255) * diffuse * ans->color->b;
		}
		free(ray);
		tmp = tmp->next;
	}
	return (bitshift_multiply(rgb));
}


void			loop_through_pixels(void *mlx, void *window, t_scene *scene)
{
	t_ray		*ray;
	t_basis		*c_basis;
	t_intersect	*ans;
	int			col;
	double 		coeffs[3];
	int			x_pix;
	int			y_pix;

	c_basis = basis_init(scene->cameras->dir);
	x_pix = 0;
	while(x_pix < scene->canvas->width)
	{
		y_pix = 0;
		while(y_pix < scene->canvas->height)
		{
			coeffs[0] = x_pix - scene->canvas->width / 2;
			coeffs[1] = scene->canvas->height / 2 - y_pix;
			coeffs[2] = scene->canvas->width / (2 *tan(scene->cameras->fov / 2));
			ray = ray_dir_from_basis(scene->cameras, c_basis, coeffs);
			ans = ray_objects_intersection(scene->objects, ray);
			col = blinn_phong(ans, scene);
			mlx_pixel_put(mlx, window, x_pix, y_pix, col);
			free(ray);
			if (ans)
			{
				free(ans->normal);
				free(ans->p_inter);
				free(ans->to_cam);
			}
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
	print_scene(scene);
}
int			main(int ac, char **av)
{
	t_scene	*scene;
	void	*mlx;
	void	*window;
	scene = define_scene();
	parse_input(scene, ac, av);


	mlx = mlx_init();
	window = mlx_new_window(mlx, scene->canvas->width, scene->canvas->height, "tracer");
	loop_through_pixels(mlx, window, scene);
	mlx_loop(mlx);
	return (0);
}