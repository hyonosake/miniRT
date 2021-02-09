/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 22:07:12 by alex              #+#    #+#             */
/*   Updated: 2021/02/09 14:26:10 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"
#include <stdio.h>


double			define_light(t_trace *trace, t_light *lights, double ambient)
{
	t_light		*tmp;
	double		index;
	t_vector	*h;
	t_vector	*l;
	double		plus;
	
	tmp = lights;
	index = ambient;
	while (tmp)
	{
		l = v_from_p(tmp->orig, trace->p_intersect);
		v_normalize(l);
		h = v_add(trace->view, l);
		v_normalize(h);
		double plus2 = v_dot_product(trace->normal, trace->view);
		plus = v_dot_product(trace->normal, l);
		if (plus < 0)
			plus = 0;
		if (plus2 < 0)
			plus2 = 0;
		index += (0.7 *pow(plus, 7) + 0.3 * pow(plus2,2))* tmp->intensity; //pow(plus, 25)
		//printf("index: %.3f\n", index);
		if (index > 1)
		{
			index = 1;
			return (1);
		}
		tmp = tmp->next;
	}
	return (index);
}



void			loop_through_pixels(void *mlx, void *window, t_scene *scene)
{
	t_ray		*ray;
	t_basis		*c_basis;
	t_vector	*up;
	t_trace		*ans;
	unsigned int c;
	t_object	*ob;
	double 		coeffs[3];
	int			rgb[3];
	int			x_pix;
	int			y_pix;

	c_basis = basis_init(scene->cameras->dir);
	x_pix = 0;
	while(x_pix < scene->canvas->width)
	{
		while(y_pix < scene->canvas->height)
		{
			coeffs[0] = x_pix - scene->canvas->width / 2;
 			coeffs[1] = scene->canvas->height / 2 - y_pix;
 			coeffs[2] = scene->canvas->width / (2 *tan(scene->cameras->fov / 2));
			ray = ray_dir_from_basis(scene->cameras, c_basis, coeffs);
			ans = ray_objects_intersection(scene->objects, ray);
			if (!ans)
				mlx_pixel_put(mlx, window, x_pix, y_pix, 0);
			else
			{
				double a = define_light(ans, scene->lights, scene->ambient->intensity);
				//define intensity in lighs function;
				mlx_pixel_put(mlx, window, x_pix, y_pix,
						intensity_and_color(ans->col, a));
			}
			free(ray);
			y_pix++;
		}
		y_pix = 0;
		x_pix++;
	}
}
t_scene		*define_scene()
{
	t_scene *new;
	
	if (!(new = (t_scene *)malloc(sizeof(t_scene))))
		error_throw(-1);
	new->canvas = NULL;
	new->cameras = NULL;
	new->objects = NULL;
	new->lights = NULL;
	new->ambient = NULL;
	return (new);
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
	//print_scene(scene);
}
int			main(int ac, char **av)
{
	t_scene	*scene;
	void	*mlx;
	void	*window;
	char	*line;
	scene = define_scene();
	parse_input(scene, ac, av);
	mlx = mlx_init();
	window = mlx_new_window(mlx, scene->canvas->width, scene->canvas->height, "plswork");
	// t_ray	*new;
	// new = (t_ray *)malloc(sizeof(t_ray));
	// new->dir = v_from_values(0,0,1);
	// new->orig = p_from_values(0,0,0);
	// t_point *or = p_from_values(0,0,100);
	// t_trace *ans;
	// ans = (t_trace *)malloc(sizeof(t_trace));
	// ans = ray_objects_intersection(scene->objects, new);
	// printf("normal:\n");

	loop_through_pixels(mlx, window, scene);
	mlx_loop(mlx);
	return (0);
}