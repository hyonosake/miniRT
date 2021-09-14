/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 09:37:24 by ffarah            #+#    #+#             */
/*   Updated: 2021/09/14 16:14:50 by ffarah           ###   ########.fr       */
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


static t_threads	*create_threads(t_scene *scene)
{
	t_threads	*tapestry = (t_threads *)calloc(N_THREADS + 1, sizeof(t_threads));
	int chunk;

	chunk = scene->canvas.width / N_THREADS;
	for (int i = 0; i < N_THREADS; i++)
	{
		tapestry[i].scene = calloc(1, sizeof(t_scene));
		memcpy(tapestry[i].scene, scene, sizeof(t_scene));
		tapestry[i].range[0] = chunk * i;
		tapestry[i].range[1] = tapestry[i].range[0] + chunk;
		printf("[%d - %d]\n", tapestry[i].range[0], tapestry[i].range[1]);
	}
	return (tapestry);
}


void			run_threads(t_scene *scene)
{
	int i = 0;

	t_threads	*threads = create_threads(scene);

	while (i < N_THREADS)
	{
		if ((pthread_create(&threads[i].thread, NULL, render_scene, &(threads[i]))) != 0)
				error_throw("Error while creating thread: start_render()");
		++i;
	}
	i = -1;
	while (++i < N_THREADS)
		pthread_join(threads[i].thread, NULL);
}

void			scene_prep(t_scene *scene)
{
	mlx_destroy_image(scene->mlx.init, scene->mlx.image);
	scene->mlx.image = mlx_new_image(scene->mlx.init,
		scene->canvas.width, scene->canvas.height);
	scene->mlx.addr = mlx_get_data_addr(scene->mlx.image, &scene->mlx.bpp,
		&scene->mlx.lsize, &scene->mlx.endian);
	run_threads(scene);
	mlx_clear_window(scene->mlx.init, scene->mlx.window);
	mlx_put_image_to_window(scene->mlx.init,
						scene->mlx.window, scene->mlx.image, 0, 0);
	mlx_string_put(scene->mlx.init, scene->mlx.window, 20, 20,
					0x00ff00, "Just a little messgae here <3");
}

int				press_key(int key, t_scene *scene)
{
	if (key == KEY_TAB || key == KEY_SPACE)
		scene->cameras = scene->cameras->next;
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
		print_cameras(scene);
	else if (key == SCREEN_SAVE)
		save_to_bmp(&scene->canvas, &scene->mlx);
	transform_scene(scene);
	scene_prep(scene);
	return (0);
}

void			create_bmp_file(t_scene *scene)
{
	save_to_bmp(&scene->canvas, &scene->mlx);
	free_scene(scene);
}

int				main(int ac, char **av)
{
	t_scene		*scene;

	scene = define_scene();
	parse_input(scene, ac, av);
	check_scene(scene);
	link_cameras(scene->cameras);
	mlx_fill(scene);
	transform_scene(scene);
	mlx_hook(scene->mlx.window, 2, 0, press_key, scene);
	mlx_hook(scene->mlx.window, 17, 0, free_scene, scene);
	if (!scene->is_bmp)
		scene_prep(scene);
	else
		create_bmp_file(scene);
	mlx_loop(scene->mlx.init);
	return (0);
}
