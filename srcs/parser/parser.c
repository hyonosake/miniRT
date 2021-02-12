/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 20:33:35 by alex              #+#    #+#             */
/*   Updated: 2021/02/12 19:45:24 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void			parse_line(char *line, t_scene *scene)
{
	char		*s;
	
	s = line;
	if (!line || *line == '\0')
		return ;
	else if (s[0] == 'R' && (s++))
		parse_resolution(s, scene);
	else if (s[0] == 'c' && (s++))
		parse_cameras(s, scene);
	else if (s[0] == 'A' && (s++))
		parse_amb_light(s, scene);
	else if (s[0] == 'l' && (s++))
		parse_lights(s, scene);
	else if (s[0] == 's' && s[1] == 'p' && (s += 2))
		parse_sphere(s, scene);
	else if (s[0] == 'p' && s[1] == 'l' && (s += 2))
	{
		printf("here\n");
		parse_plane(s, scene); 
	}
	else
		error_throw(-2);
}


t_object		*create_object(void *content, t_color *color, int type)
{
	t_object	*new;
	if (!(new = (t_object *)malloc(sizeof(t_object))))
		error_throw(-1);
	new->type = type;
	new->content = content;
	new->color = color;
	new->next = NULL;
	return (new);
}
void			parse_sphere(char *line, t_scene *scene)
{
	t_sphere	*new;
	t_color		*col;
	if(!(new = (t_sphere *)malloc(sizeof(t_sphere))))
		error_throw(-1);
	skip_spaces(&line);
	new->orig = parse_point(&line);
	skip_spaces(&line);
	new->r = atof_modified(&line) / 2;
	new->rsq = pow(new->r, 2);
	skip_spaces(&line);
	col = parse_color_triplet(&line);
	skip_spaces(&line);
	if (*line != '\0' || new->r <= 0)
		error_throw(-2);
	add_object(scene, create_object((void *)new, col, OBJ_SPHERE));
}

void			parse_plane(char *line, t_scene *scene)
{
	t_plane		*new;
	t_color		*col;

	if(!(new = (t_plane *)malloc(sizeof(t_plane))))
		error_throw(-1);
	skip_spaces(&line);
	new->orig = parse_point(&line);
	print_point(new->orig);
	skip_spaces(&line);
	new->normal = parse_vector(&line);
	skip_spaces(&line);
	col = parse_color_triplet(&line);
	skip_spaces(&line);
	if (*line != '\0' || new->normal->mod != 1)
		error_throw(-2);
	add_object(scene, create_object((void *)new, col, OBJ_PLANE));	
}


