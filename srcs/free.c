/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 10:24:41 by alex              #+#    #+#             */
/*   Updated: 2021/02/19 12:07:46 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void			free_ray(t_ray *ray)
{
	free(ray->dir);
	free(ray->orig);
	free(ray);
}

void			free_cameras(t_camera *cams)
{
	t_camera	*tmp;
	t_camera	*for_free;

	tmp = cams;
	while(tmp)
	{
		free(tmp->dir);
		free(tmp->orig);
		for_free = tmp;
		tmp = tmp->next;
		free(for_free);	
	}
}

void			free_lights(t_light *lights)
{
	t_light		*tmp;
	t_light		*for_free;

	tmp = lights;
	while(tmp)
	{
		free(tmp->orig);
		free(tmp->color);
		for_free = tmp;
		tmp = tmp->next;
		free(for_free);	
	}
}

void			free_plane(t_plane *pl)
{
	free(pl->normal);
	free(pl->orig);
}

void			free_objects(t_object *objs)
{
	t_object	*tmp;
	t_object	*for_free;

	tmp = objs;
	while (tmp)
	{
		for_free = tmp;
		free(tmp->color);
		if (tmp->type == OBJ_SPHERE)
			free(((t_sphere *)tmp->content)->orig);
		else if (tmp->type == OBJ_PLANE)
			free_plane((t_plane *)tmp->content);
		else if (tmp->type == OBJ_TRIAN)
			//free_trian((t_trian *)tmp->content);
			;
		free(for_free);
		tmp = tmp->next;
	}
}

void			free_scene(t_scene *scene)
{
	free_lights(scene->lights);
	free_objects(scene->objects);
	free(scene->canvas);
	free(scene->ambient->color);
	free(scene->ambient->orig);
	free(scene->ambient);
	free(scene);
}