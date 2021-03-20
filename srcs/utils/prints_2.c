/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 15:24:09 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/20 02:59:55 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	print_canvas(t_scene *scene)
{
	printf("--------------- SCENE ----------------\n");
	printf("width: %d\n", scene->canvas.width);
	printf("height: %d\n", scene->canvas.height);
	printf("ratio: %f\n", scene->canvas.ratio);
	printf("--------------------------------------\n");
}

void	print_vector(t_vector *v, char *s)
{
	if (!v)
	{
		printf("null\n");
		return ;
	}
	if (!s)
		printf("[%.3f %.3f %.3f]\tmod = %.3f\n",
			v->xv, v->yv, v->zv, v->mod);
	printf("%s\t[%.3f %.3f %.3f]\tmod = %.3f\n",
		s, v->xv, v->yv, v->zv, v->mod);
}

void	print_ray(t_ray *v)
{
	if (!v)
	{
		printf("null\n");
		return ;
	}
	print_vector(&v->orig, "orig:");
	print_vector(&v->dir, "dir:");
}

void	print_cameras(t_scene *scene)
{
	t_camera	*tmp;

	if (!scene->cameras)
	{
		write(1, "No cams found\n", 16);
		return ;
	}
	tmp = scene->cameras;
	printf("Standing on cam %d\n", tmp->id);
	printf("\n------------ CAM No %d --------------\n", tmp->id);
	print_vector(&tmp->dir, "dir:\t");
	print_vector(&tmp->orig, "orig:\t");
	print_vector(&tmp->saved_orig, "init orig:");
	printf("fov:\t%.3f rad\n", tmp->fov);
	printf("--------------------------------------\n");
}
