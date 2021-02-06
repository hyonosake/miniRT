/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 01:14:28 by ffarah            #+#    #+#             */
/*   Updated: 2021/02/06 17:57:44 by alex             ###   ########.fr       */
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
	printf("vector:\t[%g.3 %g.3 %g.3]\tmod = %g.3\n", v->xv, v->yv, v->zv, v->mod);
}

void	print_point(t_point *v)
{
	printf("point:\t[%g.3 %g.3 %g.3]\n", v->xp, v->yp, v->zp);
}

void	print_color(t_color *color)
{
	printf("RGB\t[%d %d %d]\n", color->r, color->g, color->b);
}

void	print_cameras(t_scene *scene)
{
	t_camera	*tmp;
	int i = 0;
	if (!scene->cameras)
	{
		write(1, "No cams found\n", 16);
		return ;
	}
	tmp = scene->cameras;
	while (tmp)
	{
		printf("\n--------- CAM No %d ----------\n", i);			i++;
		print_vector(tmp->dir);
		print_point(tmp->orig);
		printf("fov:\t%g.3 rad\n", tmp->fov);
		printf("-----------------------------\n");
		tmp = tmp->next;
	}
}

void	print_amb_light(t_scene *scene)
{
	int i = 0;
	t_light *tmp;
	tmp = scene->ambient;
	if (!tmp)
	{
		write(1, "No ambient lights\n", 25);
		return ;
	}
	while (tmp)
	{
		printf("\n--------- AMB No %d ----------\n", i);			i++;
		print_color(tmp->color);
		printf("intens\t%g.3\n", tmp->intensity);
		printf("-----------------------------\n");
		tmp = tmp->next;
	}
	
}
