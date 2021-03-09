/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 01:03:13 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/09 11:44:05 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_scene		*define_scene(void)
{
	t_scene *new;

	if (!(new = (t_scene *)malloc(sizeof(t_scene))))
		error_throw(-1);
	// new->canvas = NULL;
	new->cameras = NULL;
	new->objects = NULL;
	new->lights = NULL;
	// new->ambient = NULL;
	new->mlx_init = NULL;
	new->mlx_window = NULL;
	return (new);
}

void			add_canvas(t_scene *scene, t_canvas *new)
{
	// if (scene->canvas)
	// 	error_throw(-2);
	scene->canvas = *new;
}

void			add_camera(t_scene *scene, t_camera *cam)
{
	t_camera	*tmp;
	tmp = scene->cameras;
	if (!tmp)
	{
		scene->cameras = cam;
		cam->next = NULL;
		cam->prev = cam;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = cam;
	cam->prev = tmp;
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
