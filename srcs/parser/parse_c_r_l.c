/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_c_r_l.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:30:32 by alex              #+#    #+#             */
/*   Updated: 2021/02/16 21:23:23 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void			parse_resolution(char *line, t_scene *scene)
{
	t_canvas	*new;

	if(!(new = (t_canvas *)malloc(sizeof(t_canvas))))
		error_throw(-1);
	new->width = atoi_modified(&line);
	skip_spaces(&line);
	new->height = atoi_modified(&line);
	new->ratio = 1.0 * new->width / new->height;
	skip_spaces(&line);
	//add max-min resolution check
	if (*line)
		error_throw(-2);
	add_canvas(scene, new);
}


void			parse_cameras(char *line, t_scene *scene)
{
	t_camera	*new;
	
	if(!(new = (t_camera *)malloc(sizeof(t_camera))))
		error_throw(-1);
	new->orig = parse_point(&line);
	skip_spaces(&line);
	new->dir = parse_vector(&line);
	skip_spaces(&line);
	new->fov = atoi_modified(&line) * M_PI / 180;
	skip_spaces(&line);
	if (*line || new->fov > 179 || new->fov < 1)
		error_throw(-2);
	new->next = NULL;
	v_normalize(new->dir);
	add_camera(scene, new);
}

t_color			*parse_color_triplet(char **line)
{
	int		rgb[3];

	rgb[0] = atoi_modified(line);
	skip_spaces(line);
	if (**line != ',')
		error_throw(-2);
	++(*line);
	rgb[1] = atoi_modified(line);
	skip_spaces(line);
	if (**line != ',')
		error_throw(-2);
	++(*line);
	skip_spaces(line);
	rgb[2] = atoi_modified(line);
	skip_spaces(line);
	if (**line)
		error_throw(-2);
	return (color_create(rgb[0], rgb[1], rgb[2]));
}

void			parse_amb_light(char *line, t_scene *scene)
{
	t_light		*new;
	
	if(!(new = (t_light *)malloc(sizeof(t_light))))
		error_throw(-1);
	skip_spaces(&line);
	new->intensity = atof_modified(&line);
	skip_spaces(&line);
	new->color = parse_color_triplet(&line);
	new->next = NULL;
	add_amb_light(scene, new);
}


void			parse_lights(char *line, t_scene *scene)
{
	t_light		*new;
	
	if(!(new = (t_light *)malloc(sizeof(t_light))))
		error_throw(-1);
	new->orig = parse_point(&line);
	skip_spaces(&line);
	new->intensity = atof_modified(&line);
	skip_spaces(&line);
	new->color = parse_color_triplet(&line);
	new->next = NULL;
	add_light(scene, new);
}