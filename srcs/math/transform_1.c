/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 16:03:41 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/24 08:51:51 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void			transform_lights(t_scene *scene)
{
	t_light		*tmp;

	tmp = scene->lights;
	while (tmp)
	{
		if (tmp->type == POINTING)
			tmp->orig = v_sub(&scene->cameras->saved_orig, &tmp->saved_orig);
		else
			tmp->orig = tmp->saved_orig;
		tmp = tmp->next;
	}
}

void			transform_trian(t_trian *tr, t_vector *orig)
{
	tr->p[0] = v_sub(orig, &tr->saved_p[0]);
	tr->p[1] = v_sub(orig, &tr->saved_p[1]);
	tr->p[2] = v_sub(orig, &tr->saved_p[2]);
	tr->exc[0] = v_sub(&tr->p[0], &tr->p[1]);
	tr->exc[1] = v_sub(&tr->p[0], &tr->p[2]);
}

void			transform_objects(t_vector *orig, t_object *objs)
{
	t_object	*tmp;
	void		*c;

	tmp = objs;
	if (!tmp)
		error_throw(INPUT_ERR);
	while (tmp)
	{
		c = tmp->content;
		if (tmp->type == SPHERE)
			((t_sphere *)c)->orig = v_sub(orig, &((t_sphere *)c)->saved_orig);
		else if (tmp->type == PLANE || tmp->type == DISK)
			((t_plane *)c)->orig = v_sub(orig, &((t_plane *)c)->saved_orig);
		else if (tmp->type == SQUARE)
			((t_square *)c)->orig = v_sub(orig, &((t_square *)c)->saved_orig);
		else if (tmp->type == TRIAN)
			transform_trian((t_trian *)tmp->content, orig);
		else if (tmp->type == CYL)
			((t_cylinder *)tmp->content)->orig =
			v_sub(orig, &((t_cylinder *)tmp->content)->saved_orig);
		else if (tmp->type == DISK)
			((t_disk *)c)->orig = v_sub(orig, &((t_disk *)c)->saved_orig);
		tmp = tmp->next;
	}
}

void			transform_cameras(t_camera *cams)
{
	t_camera	*tmp;

	tmp = cams;
	tmp->orig = v_from_values(0, 0, 0);
	tmp = tmp->next;
	while (tmp != cams)
	{
		tmp->orig = v_sub(&cams->saved_orig, &tmp->saved_orig);
		tmp = tmp->next;
	}
}

void			transform_scene(t_scene *scene)
{
	scene->r_basis = basis_init(&scene->cameras->dir);
	transform_lights(scene);
	transform_objects(&scene->cameras->saved_orig, scene->objects);
	transform_cameras(scene->cameras);
}
