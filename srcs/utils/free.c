/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 10:24:41 by alex              #+#    #+#             */
/*   Updated: 2021/03/18 15:34:52 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void			free_cameras(t_camera *cams)
{
	t_camera	*tmp;
	t_camera	*for_free;

	tmp = cams->next;
	while (tmp != cams)
	{
		for_free = tmp;
		tmp = tmp->next;
		free(for_free);
	}
	free(tmp);
}

void			free_lights(t_light *lights)
{
	t_light		*tmp;
	t_light		*for_free;

	tmp = lights;
	while (tmp)
	{
		for_free = tmp;
		tmp = tmp->next;
		free(for_free);
	}
}

void			free_objects(t_object *objs)
{
	t_object	*tmp;
	t_object	*for_free;

	tmp = objs;
	while (tmp)
	{
		for_free = tmp;
		free(for_free);
		tmp = tmp->next;
	}
}

void			free_scene(t_scene *scene)
{
	free_lights(scene->lights);
	free_cameras(scene->cameras);
	free_objects(scene->objects);
	free(scene);
}
