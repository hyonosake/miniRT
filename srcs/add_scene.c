/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 01:03:13 by ffarah            #+#    #+#             */
/*   Updated: 2021/02/19 11:53:06 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void			add_canvas(t_scene *scene, t_canvas *new)
{
	if (scene->canvas)
		error_throw(-2);
	scene->canvas = new;
}

void			add_camera(t_scene *scene, t_camera *cam)
{
	t_camera	*tmp;

	tmp = scene->cameras;
	if (!tmp)
	{
		scene->cameras = cam;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = cam;
}

void			add_amb_light(t_scene *scene, t_light *amb)
{
	if (scene->ambient)
		error_throw(-2);
	scene->ambient = amb;
}

void			add_light(t_scene *scene, t_light *l)
{
	t_light		*tmp;

	tmp = scene->lights;
	if (!tmp)
	{
		scene->lights = l;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = l;
}

void			add_object(t_scene *scene, t_object *obj)
{
	t_object	*tmp;

	tmp = scene->objects;
	if (!tmp)
	{
		scene->objects = obj;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = obj;
}
