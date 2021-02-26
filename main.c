/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 22:07:12 by alex              #+#    #+#             */
/*   Updated: 2021/02/26 17:36:34 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"
#include <stdio.h>

void		link_cameras(t_camera *cams)
{
	t_camera	*head;
	t_camera	*tmp;
	head = cams;
	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = head;
	cams->prev = tmp;
}


int			main(int ac, char **av)
{
	t_scene	*scene;
	t_camera *tmp;

	scene = define_scene();
	parse_input(scene, ac, av);
	print_scene(scene);
	tmp = scene->cameras;
	transform_scene(scene, tmp);
	print_scene(scene);
	link_cameras(scene->cameras);
	while(1)
	{
		scene->mlx_init = mlx_init();
		scene->mlx_window = mlx_new_window(scene->mlx_init, scene->canvas->width, scene->canvas->height, "tracer");
		scene->mlx_image = mlx_new_image(scene->mlx_init, scene->canvas->width, scene->canvas->height);
		loop_through_pixels(scene, tmp);
		//mlx_put_image_to_window(scene->mlx, scene->mlx_window, scene->mlx_image,0,0);
		mlx_loop(scene->mlx_init);
		//if (keyhook = r)
		//tmp = tmp->next
		//if hook = l
		//tmp = tmp->prev
	}
	return (0);
}