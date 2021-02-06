/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 20:33:35 by alex              #+#    #+#             */
/*   Updated: 2021/02/06 21:21:01 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void		parse_line(char *line, t_scene *scene)
{
	char	*s;
	
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
		parse_plane(s, scene); 
	else
		error_throw(-2);
}


t_object		*create_object(void *content, t_color *color, int type, t_ray *inter)
{
	t_object	*new;
	if (!(new = (t_object *)malloc(sizeof(t_object))))
		error_throw(-1);
	new->type = type;
	new->content = content;
	new->color = color;
	new->intersect = inter;
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
	new->orig = p_from_string(&line);
	skip_spaces(&line);
	new->r = atof_modified(&line) / 2;
	new->rsq = pow(new->r, 2);
	skip_spaces(&line);
	col = parse_color_triplet(&line);
	skip_spaces(&line);
	if (*line != '\0' || new->r <= 0)
		error_throw(-2);
	add_object(scene, create_object((void *)new, col, OBJ_SPHERE, NULL));
}

void			parse_plane(char *line, t_scene *scene)
{
	t_plane		*new;
	t_color		*col;
	t_ray		*ray;
	t_vector	*tmp;

	if(!(new = (t_plane *)malloc(sizeof(t_plane))))
		error_throw(-1);
	skip_spaces(&line);
	new->orig = p_from_string(&line);
	print_point(new->orig);
	skip_spaces(&line);
	ray = new_ray(v_from_string(&line), NULL);
	print_vector(ray->dir);
	new->v1 = v_cross_product(tmp = v_from_values(0,1,0), ray->dir);
	if (v_isnull(new->v1))
	{
		free(tmp);
		tmp = v_from_values(1, 0, 0);
		new->v1 = v_cross_product(tmp, ray->dir);
	}
	new->v2 = v_cross_product(new->v1, ray->dir);
	skip_spaces(&line);
	col = parse_color_triplet(&line);
	skip_spaces(&line);
	if (*line != '\0' || ray->dir->mod != 1)
		error_throw(-2);
	free(tmp);
	add_object(scene, create_object((void *)new, col, OBJ_PLANE, ray));	
}


