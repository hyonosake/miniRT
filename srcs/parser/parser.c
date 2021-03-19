/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 20:33:35 by alex              #+#    #+#             */
/*   Updated: 2021/03/19 15:19:20 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void			make_disk(t_cylinder *cy, t_vector col,
							t_scene *scene, int flag)
{
	t_disk		*new;
	t_vector	tmp;

	if (!(new = (t_disk *)malloc(sizeof(t_disk))))
		error_throw(MALLOC_ERR);
	new->normal = cy->axis;
	new->radius = cy->r;
	tmp = point_from_vector(&cy->axis, flag * cy->len * 0.5);
	new->saved_orig = v_add(&cy->saved_orig, &tmp);
	tmp = point_from_vector(&col, 0.5);
	add_object(scene, create_object((void *)new, tmp, DISK));
}

void			parse_disk(char *line, t_scene *scene)
{
	t_disk		*new;
	t_vector	col;

	if (!(new = (t_disk *)malloc(sizeof(t_disk))))
		error_throw(MALLOC_ERR);
	skip_spaces(&line);
	new->saved_orig = parse_point(&line);
	skip_spaces(&line);
	new->normal = parse_vector(&line);
	new->radius = atof_modified(&line) * 0.5;
	skip_spaces(&line);
	col = parse_color_triplet(&line);
	skip_spaces(&line);
	v_normalize(&new->normal);
	if (*line != '\0' || !check_vector_input(&new->normal))
		error_throw(INPUT_ERR);
	add_object(scene, create_object((void *)new, col, DISK));
}

void			parse_line(char *line, t_scene *scene)
{
	char		*s;

	s = line;
	if (!line || *line == '\0')
		return ;
	else if (s[0] == 'R' && (++s))
		parse_resolution(s, scene);
	else if (s[0] == 'c' && s[1] == 'y' && (s += 2))
		parse_cylinder(s, scene);
	else if (s[0] == 'c' && (s++))
		parse_cameras(s, scene);
	else if (s[0] == 'A' && (s++))
		parse_amb_light(s, scene);
	else if (s[0] == 'l' && (s++))
		parse_lights(s, scene, POINTING);
	else if (s[0] == 's' && s[1] == 'p' && (s += 2))
		parse_sphere(s, scene);
	else if (s[0] == 'p' && s[1] == 'l' && (s += 2))
		parse_plane(s, scene);
	else if (s[0] == 's' && s[1] == 'q' && (s += 2))
		parse_square(s, scene);
	else if (s[0] == 't' && s[1] == 'r' && (s += 2))
		parse_triangle(s, scene);
	else
		parse_bonuses(line, scene);
}

void			parse_bonuses(char *line, t_scene *scene)
{
	char		*s;

	s = line;
	if (s[0] == 'l' && s[1] == 'd' && (s += 2))
		parse_lights(s, scene, DIRECT);
	else if (s[0] == 'd' && (++s))
		parse_disk(s, scene);
	else
		error_throw(INPUT_ERR);
}

void			parse_cylinder(char *line, t_scene *scene)
{
	t_cylinder	*new;
	t_vector	col;

	if (!(new = (t_cylinder *)malloc(sizeof(t_cylinder))))
		error_throw(MALLOC_ERR);
	skip_spaces(&line);
	new->saved_orig = parse_point(&line);
	skip_spaces(&line);
	new->axis = parse_point(&line);
	skip_spaces(&line);
	new->r = atof_modified(&line) * 0.5;
	new->rsq = new->r * new->r;
	skip_spaces(&line);
	new->len = atof_modified(&line);
	skip_spaces(&line);
	col = parse_color_triplet(&line);
	new->lhalf = new->len * 0.5;
	skip_spaces(&line);
	if (*line != '\0' || !check_vector_input(&new->axis) ||
		new->r <= 0 || new->len <= 0)
		error_throw(INPUT_ERR);
	v_normalize(&new->axis);
	make_disk(new, col, scene, 1);
	make_disk(new, col, scene, -1);
	add_object(scene, create_object((void *)new, col, CYL));
}
