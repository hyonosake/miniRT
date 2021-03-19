/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 09:37:24 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/19 16:02:52 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"
#include <stdio.h>

void			link_cameras(t_camera *cams)
{
	t_camera	*head;
	t_camera	*tmp;

	head = cams;
	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = head;
}

void			check_scene(t_scene *scene)
{
	if (scene->ambient.intensity == -1 && !scene->lights)
		error_throw(INPUT_ERR);
	if (!scene->cameras)
		error_throw(INPUT_ERR);
}

int				press_key(int key, t_scene *scene)
{
	if (key == KEY_TAB)
	{
		//mlx_destroy_image(scene->mlx.init, scene->mlx.image);
		scene->cameras = scene->cameras->next;
	}
	else if (key == KEY_ESC)
	{
		free_scene(scene);
		exit(0);
	}
	else if (key == W || key == A || key == S || key == D)
		transform_wasd(key, scene->cameras, &scene->r_basis);
	else if (key == UR || key == DR || key == LR || key == RR)
		rotate_cam(key, scene->cameras, scene);
	else if (key == C)
		;
		//print_cameras(scene);
	transform_scene(scene);
	loop_through_pixels(scene);
	mlx_put_image_to_window(scene->mlx.init,
					scene->mlx.window, scene->mlx.image, 0, 0);
	mlx_string_put(scene->mlx.init, scene->mlx.window, 20, 20,
					0x00ff00, "cam No");
	return (0);
}

int				main(int ac, char **av)
{
	t_scene		*scene;

	scene = define_scene();
	parse_input(scene, ac, av);
	link_cameras(scene->cameras);
	check_scene(scene);
	mlx_fill(scene);
	transform_scene(scene);
	loop_through_pixels(scene);
	mlx_hook(scene->mlx.window, 2, 0, press_key, scene);
	if (!scene->is_bmp)
	{
		mlx_put_image_to_window(scene->mlx.init,
						scene->mlx.window, scene->mlx.image, 0, 0);
		mlx_loop(scene->mlx.init);
	}
	else
	{
		save_to_bmp(&scene->canvas, &scene->mlx);
		mlx_destroy_image(scene->mlx.init, scene->mlx.image);
		free_scene(scene);
	}
	return (0);
}
