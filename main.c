/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 22:07:12 by alex              #+#    #+#             */
/*   Updated: 2021/02/10 17:56:27 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"
#include <stdio.h>

int					bitshift_multiply(t_color *col, double intens)
{
	int				res;
	int				rgb[3];
	int i;

	i = 0;
	rgb[0] = col->r * intens;
	rgb[1] = col->g * intens;
	rgb[2] = col->b * intens;
	while (i < 3)
	{
		if (rgb[i] > 255)
			rgb[i] = 255;
		i++;
	}
	res =  rgb[0] << 16 | rgb[1] << 8 | rgb[2];
	printf("col = %d\n", res);
	return (res);
}


int					blinn_phong(t_intersect *ans, t_light *lights, t_light *amb)
{
	t_vector		*l;
	t_light			*tmp;
	t_vector		*h;
	unsigned int	col;
	double			spec;
	double 			intensity;
	double			diffuse;
	tmp = lights;
	if (!ans)
		return BACKGROUND_COLOR;
	intensity = amb->intensity;
	while (tmp)
	{
		spec = 0;
		l = v_from_p(tmp->orig, ans->p_inter);
		v_normalize(l);
		//h = v_add(l,ans->to_cam);
		//v_normalize(h);
		//spec = v_dot_product(ans->normal, h);
		//print_vector(ans->normal);
		diffuse = v_dot_product(ans->normal, l);
		//print_vector(ans->normal);
		//print_vector(l);
		//printf("dot: %.3f\n", diffuse);
		// if (spec < 0)
		// 	spec = 0;
		if (diffuse < 0)
			diffuse = 0;
		//printf("diffuse = %.3f\n", diffuse);
		intensity+=  (pow(spec, 15) + pow(diffuse, 2)) * tmp->intensity;
		if (intensity >= 1)
			break ;
		tmp = tmp->next;
	}
	printf("intens = %.2f\n", intensity);
	return (bitshift_multiply(ans->color, intensity));
}


void			loop_through_pixels(void *mlx, void *window, t_scene *scene)
{
	t_ray		*ray;
	t_basis		*c_basis;
	t_vector	*up;
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
			//printf("[%i %i]", x_pix, y_pix);
			coeffs[0] = x_pix - scene->canvas->width / 2;
			coeffs[1] = scene->canvas->height / 2 - y_pix;
			coeffs[2] = scene->canvas->width / (2 *tan(scene->cameras->fov / 2));
			ray = ray_dir_from_basis(scene->cameras, c_basis, coeffs);
			ans = ray_objects_intersection(scene->objects, ray);
			col = blinn_phong(ans,scene->lights, scene->ambient);
			//printf("here??\n");
			mlx_pixel_put(mlx, window, x_pix, y_pix, col);
			//printf("still here?\n");
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
	print_scene(scene);
}
int			main(int ac, char **av)
{
	t_scene	*scene;
	void	*mlx;
	void	*window;
	char	*line;
	scene = define_scene();
	parse_input(scene, ac, av);
	// t_ray	*new;
	// new = (t_ray *)malloc(sizeof(t_ray));
	// new->dir = v_from_values(0,0,1);
	// new->orig = p_from_values(0,0,0);
	// t_point *or = p_from_values(0,0,100);
	// t_trace *ans;
	// ans = (t_trace *)malloc(sizeof(t_trace));
	// ans = ray_objects_intersection(scene->objects, new);
	// printf("normal:\n");


	mlx = mlx_init();
	window = mlx_new_window(mlx, scene->canvas->width, scene->canvas->height, "tracer");
	loop_through_pixels(mlx, window, scene);
	mlx_loop(mlx);
	return (0);
}