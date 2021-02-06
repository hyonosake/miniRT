/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 20:33:35 by alex              #+#    #+#             */
/*   Updated: 2021/02/06 17:53:52 by alex             ###   ########.fr       */
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
	else
		error_throw(-2);
}


t_vector			*parse_vector(char **line)
{
	t_vector		*new;
	skip_spaces(line);
	new = v_from_string(line);
	skip_spaces(line);
	return (new);
}

t_point			*parse_point(char **line)
{
	t_point		*new;
	skip_spaces(line);
	new = p_from_string(line);
	skip_spaces(line);
	return (new);
}

t_color		*color_create(int r, int g, int b)
{
	t_color	*new;
	
	if(!(new = (t_color *)malloc(sizeof(t_color))))
		error_throw(-1);
	if (r > 255 || r < 0 || g > 255 || g < 0 ||
		b > 255 || b < 0)
		error_throw(-2);
	new->r = r;
	new->g = g;
	new->b = b;
	return (new);
}