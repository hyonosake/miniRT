/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 22:07:12 by alex              #+#    #+#             */
/*   Updated: 2021/03/06 22:45:33 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"
#include <stdio.h>


int	press_key(int key, t_scene *scene);

void			link_cameras(t_camera *cams)
{
	t_camera	*head;
	t_camera	*tmp;
	head = cams;
	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = head;
	//cams->prev = tmp;
}


int				main(int ac, char **av)
{
	t_scene		*scene;
	scene = define_scene();
	parse_input(scene, ac, av);
	link_cameras(scene->cameras);
	print_cameras(scene);
	print_objects(scene);
	printf("\n============= INIT =============\n");
	transform_scene(scene);
	//print_cameras(scene);
	print_objects(scene);
	scene->mlx_init = mlx_init();
	scene->mlx_window = mlx_new_window(scene->mlx_init, scene->canvas.width, scene->canvas.height, "tracer");
	scene->mlx_image = mlx_new_image(scene->mlx_init, scene->canvas.width, scene->canvas.height);
	mlx_hook(scene->mlx_window, 2, 0, press_key, scene);
	loop_through_pixels(scene);
	//mlx_put_image_to_window(scene->mlx_init, scene->mlx_window, scene->mlx_image,0,0);
	mlx_loop(scene->mlx_init);
	return (0);
}

int	press_key(int key, t_scene *scene)
{
	if (key == KEY_TAB) //tab
	{
		//if (scene->cameras->next)
		scene->cameras = scene->cameras->next;
	}
	else if (key == KEY_ESC)
	{
		free_scene(scene);
  		exit(0);
	}
	else if (key == 13)
		++scene->cameras->orig.zv;
	else if (key == 0)
		--scene->cameras->orig.xv;
	else if (key == 1)
		--scene->cameras->orig.zv;
	else if (key == 2)
		++scene->cameras->orig.xv;
	transform_scene(scene);
	//print_cameras(scene);
	print_objects(scene);
	print_scene(scene);
	loop_through_pixels(scene);
	return (0);
}