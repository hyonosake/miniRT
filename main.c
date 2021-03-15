/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 09:37:24 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/15 15:03:47 by alex             ###   ########.fr       */
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
	//print_cameras(scene);
	//print_scene(scene);
	//print_objects(scene);
	printf("\n============= INIT =============\n");
	transform_scene(scene);
	print_objects(scene);
	//error_throw(-1);
	//print_cameras(scene);
	//print_scene(scene);
	scene->mlx_init = mlx_init();
	scene->mlx_window = mlx_new_window(scene->mlx_init, scene->canvas.width, scene->canvas.height, "tracer");
	scene->mlx_image = mlx_new_image(scene->mlx_init, scene->canvas.width, scene->canvas.height);
	mlx_hook(scene->mlx_window, 2, 0, press_key, scene);
	loop_through_pixels(scene);
	//mlx_put_image_to_window(scene->mlx_init, scene->mlx_window, scene->mlx_image,0,0);
	mlx_string_put(scene->mlx_init, scene->mlx_window, 20, 20, 0xFFFFFF, "Scene av[0]");
	mlx_loop(scene->mlx_init);
	return (0);
}


void	transform_wasd(int key, t_camera *cam, t_basis *b)
{
	if (key == 13)
		cam->saved_orig = v_add(&cam->saved_orig, &b->k);
	else if (key == 0)
		cam->saved_orig = v_sub(&b->i, &cam->saved_orig);
	else if (key == 1)
		cam->saved_orig = v_sub(&b->k, &cam->saved_orig);
	else if (key == 2)
		cam->saved_orig = v_add(&cam->saved_orig, &b->i);
}

int		press_key(int key, t_scene *scene)
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
	else if (key == 13 || key == 0 || key == 1 || key == 2)
		transform_wasd(key, scene->cameras, &scene->r_basis);
	else if (key == 8)
		print_cameras(scene);
	//	++scene->cameras->saved_orig.zv;
	//else if (key == 0)
	//	--scene->cameras->saved_orig.xv;
	//else if (key == 1)
	//	--scene->cameras->saved_orig.zv;
	//else if (key == 2)
	//	++scene->cameras->saved_orig.xv;
	transform_scene(scene);
	//mlx_string_put(scene->mlx_init, scene->mlx_window, 20, 20, 0xFFFFFF, "Scene av[0]");
	//print_cameras(scene);
	//print_scene(scene);
	loop_through_pixels(scene);
	return (0);
}