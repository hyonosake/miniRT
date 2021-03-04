/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 20:33:35 by alex              #+#    #+#             */
/*   Updated: 2021/03/03 14:30:44 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_object		*create_object(void *content, t_vector color, int type)
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

void	parse_input(t_scene *scene, int ac, char **av)
{
	char *line;
	int res;
	int	i;
	int fd;
	
	fd = open(av[1], O_RDONLY);
	i = 0;
	if (ac == 3)
		//parse save
		;
	if (ac < 2 || ac > 3)
		error_throw(-2);
	while (av[1][i] != '.' && av[1][i])
		i++;
	if (!av[1][i] || (av[1][i+1] != 'r' && av[1][i+2] != 't') || fd < 0)
		error_throw(-3);
	while((res = get_next_line(fd, &line)) > 0)
	{
		if (*line == '#')
			continue ;
		parse_line(line, scene);
		free(line);
	}
}

void			parse_square(char *line, t_scene *scene)
{
	t_square	*new;
	t_vector	col;

	if(!(new = (t_square *)malloc(sizeof(t_square))))
		error_throw(-1);
	skip_spaces(&line);
	new->orig = parse_point(&line);
	skip_spaces(&line);
	new->normal = parse_vector(&line);
	v_normalize(&new->normal);
	skip_spaces(&line);
	new->a = atof_modified(&line);
	new->asq = new->a * new->a;
	skip_spaces(&line);
	col = parse_color_triplet(&line);
	skip_spaces(&line);
	if (*line != '\0' || !check_vector_input(&new->normal))
		error_throw(-2);
	add_object(scene, create_object((void *)new, col, OBJ_SQUARE));
}

void			parse_line(char *line, t_scene *scene)
{
	char		*s;
	
	s = line;
	//printf("%c%c\n", line[0], line[1]);
	if (!line || *line == '\0')
		return ;
	else if (s[0] == 'R' && (s++))
		parse_resolution(s, scene);
	else if (s[0] == 'c' && (s++))
		parse_cameras(s, scene);
	else if (s[0] == 'A' && (s++))
		parse_amb_light(s, scene);
	else if (s[0] == 'l' && (s++))
		parse_lights(s, scene, 1);
	else if (s[0] == 's' && s[1] == 'p' && (s += 2))
		parse_sphere(s, scene);
	else if (s[0] == 'p' && s[1] == 'l' && (s += 2))
		parse_plane(s, scene); 
	else if (s[0] == 'd' && (s++))
		parse_lights(s, scene, 2);
	else if (s[0] == 's' && s[1] == 'q' && (s += 2))
		parse_square(s, scene);
	else
		error_throw(-2);
}

void			parse_sphere(char *line, t_scene *scene)
{
	t_sphere	*new;
	t_vector	col;
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
	t_vector	col;

	if(!(new = (t_plane *)malloc(sizeof(t_plane))))
		error_throw(-1);
	skip_spaces(&line);
	new->orig = parse_point(&line);
	skip_spaces(&line);
	new->normal = parse_vector(&line);
	v_normalize(&new->normal);
	skip_spaces(&line);
	col = parse_color_triplet(&line);
	skip_spaces(&line);
	if (*line != '\0' || !check_vector_input(&new->normal))
		error_throw(-2);
	add_object(scene, create_object((void *)new, col, OBJ_PLANE));	
}


