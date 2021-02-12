/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 22:07:12 by alex              #+#    #+#             */
/*   Updated: 2021/02/12 11:30:58 by alex             ###   ########.fr       */
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
	return (res);
}


int					blinn_phong(t_intersect *ans, t_scene *scene)
{
	t_vector		*l;
	t_light			*tmp;
	//t_vector		*h;
	t_intersect		*shad;
	double 			intensity;
	double			diffuse;
	int				aaa;
	tmp = scene->lights;
	if (!ans)
		return BACKGROUND_COLOR;
	intensity = scene->ambient->intensity;
	aaa = 0;
	while (tmp)
	{
		l = v_from_p(tmp->orig, ans->p_inter);
		v_normalize(l);
		t_vector *light_col = v_from_values(tmp->color->r / 255,
					tmp->color->g / 255, tmp->color->b / 255);
		//need to do smth and free
		t_ray *ray = new_ray(v_cpy(l), p_cpy(ans->p_inter));
		if ((shad = ray_objects_intersection(scene->objects, ray)) == NULL)
		{
			diffuse = v_dot_product(ans->normal, l);
			if (diffuse < 0)
				diffuse = 0;
			light_col = v_by_scalar(light_col, tmp->intensity * (diffuse));
			aaa = (int)(light_col->xv * ans->color->r) << 16 |
			 (int)(light_col->yv * ans->color->g) << 8 |
			 (int)(light_col->zv * ans->color->b);
		}
		free(ray);
		tmp = tmp->next;
	}
	return (aaa);
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