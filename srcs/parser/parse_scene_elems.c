/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene_elems.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:30:32 by alex              #+#    #+#             */
/*   Updated: 2021/03/22 13:53:00 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void			parse_resolution(char *line, t_scene *scene)
{
	static int	i;

	if (i || !(++line))
		error_throw(INPUT_ERR);
	scene->canvas.width = atoi_modified(&line);
	skip_spaces(&line);
	scene->canvas.height = atoi_modified(&line);
	if (scene->canvas.width < 0 || scene->canvas.width > MAXRES_X)
		scene->canvas.width = RES_X;
	if (scene->canvas.height < 0 || scene->canvas.height > MAXRES_Y)
		scene->canvas.height = RES_Y;
	else if (scene->canvas.width < scene->canvas.height)
	{
		scene->canvas.width = RES_X;
		scene->canvas.height = RES_Y;
	}
	scene->canvas.ratio = 1.0 * scene->canvas.width / scene->canvas.height;
	skip_spaces(&line);
	if (*line)
		error_throw(INPUT_ERR);
	++i;
}

void			parse_cameras(char *line, t_scene *scene)
{
	t_camera	*new;
	static int	i;

	if (!(new = (t_camera *)malloc(sizeof(t_camera))))
		error_throw(MALLOC_ERR);
	if (!(++line))
		error_throw(INPUT_ERR);
	new->saved_orig = parse_point(&line);
	skip_spaces(&line);
	new->dir = parse_point(&line);
	skip_spaces(&line);
	new->fov = atoi_modified(&line);
	skip_spaces(&line);
	if (*line || new->fov > 179 || new->fov < 1 ||
		!check_vector_input(&new->dir))
		error_throw(INPUT_ERR);
	new->fov *= M_PI / 180;
	new->next = NULL;
	new->prev = NULL;
	new->id = i++;
	v_normalize(&new->dir);
	add_camera(scene, new);
}

void			parse_amb_light(char *line, t_scene *scene)
{
	static int	i;

	if (i != 0 || !(++line))
		error_throw(INPUT_ERR);
	skip_spaces(&line);
	scene->ambient.intensity = atof_modified(&line);
	if (scene->ambient.intensity < 0 || scene->ambient.intensity > 1)
		error_throw(INPUT_ERR);
	skip_spaces(&line);
	scene->ambient.color = parse_color_triplet(&line);
	i++;
}

void			parse_lights(char *line, t_scene *scene, int type)
{
	t_light		*new;

	if (!(new = (t_light *)malloc(sizeof(t_light))))
		error_throw(MALLOC_ERR);
	if (!(line += 2))
		error_throw(INPUT_ERR);
	new->type = type;
	new->saved_orig = parse_point(&line);
	skip_spaces(&line);
	new->intensity = atof_modified(&line);
	skip_spaces(&line);
	new->color = parse_color_triplet(&line);
	skip_spaces(&line);
	new->next = NULL;
	if (*line || (!check_vector_input(&new->orig) && new->type == DIRECT) ||
		new->intensity < 0 || new->intensity > 1)
		error_throw(INPUT_ERR);
	add_light(scene, new);
}
