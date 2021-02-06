/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 01:03:13 by ffarah            #+#    #+#             */
/*   Updated: 2021/02/06 17:52:55 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"


void		add_canvas(t_scene *scene, t_canvas *new)
{
	if (scene->canvas)
		error_throw(-2);
	scene->canvas = new;
}

void	add_camera(t_scene *scene, t_camera *cam)
{
	t_camera *tmp;

	tmp = scene->cameras;
	if (!tmp)
	{
		scene->cameras = cam;
		return ;
	}
	while(tmp->next)
		tmp = tmp->next;
	tmp->next = cam;
}

void		add_light(t_light **lights, t_light *amb)
{
	t_light *tmp;

	tmp = *lights;
	if (!tmp)
	{
		*lights = amb;
		return ;
	}
	while(tmp->next)
		tmp = tmp->next;
	tmp->next = amb;
}

