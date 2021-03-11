/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_c_r_l.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:30:32 by alex              #+#    #+#             */
/*   Updated: 2021/03/11 21:20:18 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void			parse_resolution(char *line, t_scene *scene)
{
	static int	i;
	if (i)
		error_throw(-2);
	scene->canvas.width = atoi_modified(&line);
	skip_spaces(&line);
	scene->canvas.height = atoi_modified(&line);
	scene->canvas.ratio = 1.0 * scene->canvas.width / scene->canvas.height;
	skip_spaces(&line);
	//add max-min resolution check
	if (*line)
		error_throw(-2);
	i++;
	// add_canvas(scene, new);
}

void			parse_cameras(char *line, t_scene *scene)
{
	t_camera	*new;
	static int	i;
	
	if(!(new = (t_camera *)malloc(sizeof(t_camera))))
		error_throw(-1);
	new->saved_orig = parse_point(&line);
	skip_spaces(&line);
	new->dir = parse_vector(&line);
	skip_spaces(&line);
	new->fov = atoi_modified(&line);
	skip_spaces(&line);
	if (*line || new->fov > 179 || new->fov < 1 || !check_vector_input(&new->dir))
		error_throw(-2);
	new->fov *= M_PI / 180;
	new->next = NULL;
	new->prev = NULL;
	new->id = i++;
	v_normalize(&new->dir);
	add_camera(scene, new);
}

t_vector	parse_color_triplet(char **line)
{
	float		rgb[3];

	rgb[0] = 1.0 * atoi_modified(line) * VECTORIZE_COLOR;
	skip_spaces(line);
	if (**line != ',')
		error_throw(-2);
	++(*line);
	rgb[1] = 1.0 * atoi_modified(line) * VECTORIZE_COLOR;
	skip_spaces(line);
	if (**line != ',')
		error_throw(-2);
	++(*line);
	skip_spaces(line);
	rgb[2] = 1.0 * atoi_modified(line) * VECTORIZE_COLOR;
	skip_spaces(line);
	if (**line)
		error_throw(-2);
	return (v_from_values(rgb[0], rgb[1], rgb[2]));
}

void			parse_amb_light(char *line, t_scene *scene)
{
	static int	i;

	if (i != 0)
		error_throw(-2);
	skip_spaces(&line);
	scene->ambient.intensity = atof_modified(&line);
	skip_spaces(&line);
	scene->ambient.color = parse_color_triplet(&line);
	i++;
}


void			parse_lights(char *line, t_scene *scene, int type)
{
	t_light		*new;
	
	if(!(new = (t_light *)malloc(sizeof(t_light))))
		error_throw(-1);
	new->type = type;
	printf("%c\n", *line);
	new->saved_orig = parse_point(&line);
	skip_spaces(&line);
	new->intensity = atof_modified(&line);
	skip_spaces(&line);
	new->color = parse_color_triplet(&line);
	skip_spaces(&line);
	new->next = NULL;
	if (*line || (!check_vector_input(&new->orig) && new->type == DIRECT))
		error_throw(-2);
	add_light(scene, new);
}