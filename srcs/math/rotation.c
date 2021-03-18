/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 11:49:43 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/18 16:03:34 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

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

void			rotate_cam(int key, t_camera *cam, t_scene *scene)
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
