/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_c_r_l.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:30:32 by alex              #+#    #+#             */
/*   Updated: 2021/02/08 17:31:48 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../includes/parser.h"

void			parse_resolution(char *line, t_scene *scene)
{
	t_canvas	*new;

	if(!(new = (t_canvas *)malloc(sizeof(t_canvas))))
		error_throw(-1);
	skip_spaces(&line);
	new->width = atoi_modified(&line);
	skip_spaces(&line);
	new->height = atoi_modified(&line);
	skip_spaces(&line);
	new->width = new->width > 5120 ? 5120 : new->width;
	new->height = new->height > 2880 ? 2880 : new->height;
	if (*line != '\0' || new->width <= 0 || new->height <= 0)
		error_throw(-2);
	new->ratio = new->width / new->height;
	add_canvas(scene, new);
}


void			parse_cameras(char *line, t_scene *scene)
{
	t_camera	*new;

	if(!(new = (t_camera *)malloc(sizeof(t_camera))))
		error_throw(-1);
	new->orig = parse_point(&line);
	new->dir = parse_vector(&line);
	if (new->dir->mod != 1)
		error_throw(-2);
	skip_spaces(&line);
	new->fov = atoi_modified(&line);
	if (new->fov < 1 || new->fov > 179)
		error_throw(-2);
	new->fov *= M_PI / 180;
	skip_spaces(&line);
	if (*line != '\0')
		error_throw(-2);
	new->next = NULL;
	add_camera(scene, new);
}

t_color			*parse_color_triplet(char **line)
{
	
	int		rgb[3];
	skip_spaces(line);
	rgb[0] = atoi_modified(line);
	skip_spaces(line);
	if (**line == ',')
		++(*line);
	skip_spaces(line);
	rgb[1] = atoi_modified(line);
	skip_spaces(line);
	if (**line == ',')
		++(*line);
	skip_spaces(line);
	rgb[2] = atoi_modified(line);
	return (color_create(rgb[0], rgb[1], rgb[2]));
}

void			parse_amb_light(char *line, t_scene *scene)
{
	t_light		*new;
	
	if(!(new = (t_light *)malloc(sizeof(t_light))))
		error_throw(-1);
	skip_spaces(&line);
	new->orig = NULL;
	new->next = NULL;
	new->intensity = atof_modified(&line);
	if (new->intensity < 0 || new->intensity > 1)
		error_throw(-2);
	skip_spaces(&line);
	new->color = parse_color_triplet(&line);
	skip_spaces(&line);
	if (*line != '\0')
		error_throw(-2);
	add_amb_light(scene, new);
}


void			parse_lights(char *line, t_scene *scene)
{
	t_light		*new;
	
	if(!(new = (t_light *)malloc(sizeof(t_light))))
		error_throw(-1);
	skip_spaces(&line);
	new->orig = p_from_string(&line);
	new->next = NULL;
	skip_spaces(&line);
	new->intensity = atof_modified(&line);
	skip_spaces(&line);
	new->color = parse_color_triplet(&line);
	skip_spaces(&line);
	if (*line != '\0' || new->intensity < 0 || new->intensity > 1)
		error_throw(-2);
	add_light(scene, new);
}