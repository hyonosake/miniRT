/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 01:03:13 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/18 15:34:26 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_scene			*define_scene(void)
{
	t_scene		*new;

	if (!(new = (t_scene *)malloc(sizeof(t_scene))))
		error_throw(MALLOC_ERR);
	new->cameras = NULL;
	new->objects = NULL;
	new->lights = NULL;
	new->mlx.image = NULL;
	new->mlx.init = NULL;
	new->mlx.addr = NULL;
	new->mlx.window = NULL;
	new->is_bmp = 0;
	new->ambient.intensity = -1;
	return (new);
}

int				ft_isspace(char ch)
{
	if (ch == ' ' || ch == '\t')
		return (1);
	return (0);
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
