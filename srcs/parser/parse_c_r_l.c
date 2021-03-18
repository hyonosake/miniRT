/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_c_r_l.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:30:32 by alex              #+#    #+#             */
/*   Updated: 2021/03/18 15:12:10 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void			parse_resolution(char *line, t_scene *scene)
{
	static int	i;

	if (i)
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
	new->saved_orig = parse_point(&line);
	skip_spaces(&line);
	new->dir = parse_vector(&line);
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

t_vector		parse_color_triplet(char **line)
{
	float		rgb[3];
	t_vector	rgb_v;

	rgb[0] = 1.0 * atoi_modified(line) * VECTORIZE_COLOR;
	skip_spaces(line);
	if (**line != ',')
		error_throw(INPUT_ERR);
	++(*line);
	rgb[1] = 1.0 * atoi_modified(line) * VECTORIZE_COLOR;
	skip_spaces(line);
	if (**line != ',')
		error_throw(INPUT_ERR);
	++(*line);
	skip_spaces(line);
	rgb[2] = 1.0 * atoi_modified(line) * VECTORIZE_COLOR;
	skip_spaces(line);
	rgb_v = v_from_values(rgb[0], rgb[1], rgb[2]);
	if (**line || !check_vector_input(&rgb_v))
		error_throw(INPUT_ERR);
	return (rgb_v);
}

void			parse_amb_light(char *line, t_scene *scene)
{
	static int	i;

	if (i != 0)
		error_throw(INPUT_ERR);
	skip_spaces(&line);
	scene->ambient.intensity = atof_modified(&line);
	skip_spaces(&line);
	scene->ambient.color = parse_color_triplet(&line);
	i++;
}

void			parse_lights(char *line, t_scene *scene, int type)
{
	t_light		*new;

	if (!(new = (t_light *)malloc(sizeof(t_light))))
		error_throw(MALLOC_ERR);
	new->type = type;
	new->saved_orig = parse_point(&line);
	skip_spaces(&line);
	new->intensity = atof_modified(&line);
	skip_spaces(&line);
	new->color = parse_color_triplet(&line);
	skip_spaces(&line);
	new->next = NULL;
	if (*line || (!check_vector_input(&new->orig) && new->type == DIRECT))
		error_throw(INPUT_ERR);
	add_light(scene, new);
}
