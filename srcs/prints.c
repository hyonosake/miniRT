/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 01:14:28 by ffarah            #+#    #+#             */
/*   Updated: 2021/02/06 03:26:47 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	print_canvas(t_scene *scene)
{
	if (!scene->canvas)
		write(1, "No scene found\n", 16);
	else
	{
		printf("--------- SCENE ---------\n");
		printf("width: %d\n", scene->canvas->width);
		printf("height: %d\n", scene->canvas->height);
		printf("ratio: %f\n", scene->canvas->ratio);
		printf("-------------------------\n");
	}
}

void	print_vector(t_vector *v)
{
	printf("vector: [%f %f %f]\tmod = %f\n", v->xv, v->yv, v->zv, v->mod);
}

void	print_point(t_point *v)
{
	printf("point: [%f %f %f]\n", v->xp, v->yp, v->zp);
}

void	print_cameras(t_scene *scene)
{
	t_camera	*tmp;
	int i = 0;
	if (!scene->cameras)
		write(1, "No cams found\n", 16);
	else
	{
		tmp = scene->cameras;
		while (tmp)
		{
			printf("--------- CAM No %d ---------\n", i);
			i++;
			print_vector(scene->cameras->dir);
			print_point(scene->cameras->orig);
			printf("-----------------------------\n");
			tmp = tmp->next;
		}
		
	}
}
