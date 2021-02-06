/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 20:33:35 by alex              #+#    #+#             */
/*   Updated: 2021/02/06 03:28:10 by ffarah           ###   ########.fr       */
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
	else
		error_throw(-2);
}

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
	skip_spaces(&line);
	new->orig = p_from_string(&line);
	print_point(new->orig);
	skip_spaces(&line);
	printf("here\n");
	new->dir = v_from_string(&line);
	print_vector(new->dir);
	print_point(new->orig);
	if (new->dir->mod != 1)
		error_throw(-2);
	skip_spaces(&line);
	new->fov = atoi_modified(&line);
	if (new->fov < 1 || new->fov > 179)
		error_throw(-2);
	skip_spaces(&line);
	if (*line != '\0')
		error_throw(-2);
	new->next = NULL;
	add_camera(scene, new);
}

void	add_canvas(t_scene *scene, t_canvas *new)
{
	if (scene->canvas)
		error_throw(-2);
	scene->canvas = new;
}

void	add_camera(t_scene *scene, t_camera *cam)
{
	t_camera *tmp;

	tmp = scene->cameras;
	if (!tmp)
	{
		scene->cameras = cam;
		return ;
	}
	while(tmp->next)
		tmp = tmp->next;
	tmp->next = cam;
}