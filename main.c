/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 22:07:12 by alex              #+#    #+#             */
/*   Updated: 2021/02/24 12:55:53 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"
#include <stdio.h>

int			main(int ac, char **av)
{
	t_scene	*scene;
	t_camera *tmp;

	scene = define_scene();
	//t_basis	*c_matrix;
	parse_input(scene, ac, av);
	//print_scene(scene);
	tmp = scene->cameras;
	transform_scene(scene, tmp);
	print_scene(scene);
	scene->mlx = mlx_init();
	scene->window = mlx_new_window(scene->mlx, scene->canvas->width, scene->canvas->height, "tracer");
	loop_through_pixels(scene, tmp);
	mlx_loop(scene->mlx);
	return (0);
}