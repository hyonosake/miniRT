/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 09:37:24 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/16 23:06:45 by ffarah           ###   ########.fr       */
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

void			rotate_y_axis(t_vector *v, float s, float c)
{
	v->zv = v->zv * c - v->xv * s;
	v->xv = v->zv * s + v->xv * c;  
}

void			rotate_x_axis(t_vector *v, float s, float c)
{
	v->zv = v->zv * c - v->yv * s;
	v->yv = v->zv * s + v->yv * c;  
}
void			my_pixel_put(t_mlx *mlx, int x_pix, int y_pix, int col)
{
    char    *dst;

    dst = mlx->addr + (y_pix * mlx->lsize + x_pix * (mlx->bpp / 8));
    *(unsigned int*)dst = col;
}

void			mlx_fill(t_scene *scene)
{
	
	scene->mlx.init = mlx_init();
	scene->mlx.window = mlx_new_window(scene->mlx.init, scene->canvas.width, scene->canvas.height, "tracer");
	scene->mlx.image = mlx_new_image(scene->mlx.init, scene->canvas.width, scene->canvas.height);
	scene->mlx.addr = mlx_get_data_addr(scene->mlx.image, &scene->mlx.bpp,
										&scene->mlx.lsize, &scene->mlx.endian);
}
int				main(int ac, char **av)
{
	t_scene		*scene;

	scene = define_scene();
	parse_input(scene, ac, av);
	link_cameras(scene->cameras);
	printf("\n============= INIT =============\n");
	transform_scene(scene);
	mlx_fill(scene);
	loop_through_pixels(scene);
	//mlx_destroy_image(scene->mlx.init, scene->mlx.image);
	mlx_hook(scene->mlx.window, 2, 0, press_key, scene);
	mlx_put_image_to_window(scene->mlx.init, scene->mlx.window, scene->mlx.image, 0, 0);
	mlx_loop(scene->mlx.init);
	return (0);
}


void			transform_wasd(int key, t_camera *cam, t_basis *b)
{
	if (key == W)
		cam->saved_orig = v_add(&cam->saved_orig, &b->k);
	else if (key == A)
		cam->saved_orig = v_sub(&b->i, &cam->saved_orig);
	else if (key == S)
		cam->saved_orig = v_sub(&b->k, &cam->saved_orig);
	else if (key == D)
		cam->saved_orig = v_add(&cam->saved_orig, &b->i);
}

void	rotate_cam(int key, t_camera *cam, t_scene *scene)
{
	if (key == RR)
		rotate_y_axis(&cam->dir, sin(THETA), cos(THETA));
	else if (key == LR)
		rotate_y_axis(&cam->dir, -sin(THETA), cos(THETA));
	else if (key == UR)
		rotate_x_axis(&cam->dir, sin(THETA), cos(THETA));
	else if (key == DR)
		rotate_x_axis(&cam->dir, -sin(THETA), cos(THETA));
	scene->r_basis = basis_init(&cam->dir);
}

int		press_key(int key, t_scene *scene)
{
	if (key == KEY_TAB)
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
	transform_scene(scene);
	//mlx_destroy_image(scene->mlx.init, scene->mlx.image);
	loop_through_pixels(scene);
	mlx_put_image_to_window(scene->mlx.init, scene->mlx.window, scene->mlx.image,0,0);
	return (0);
}