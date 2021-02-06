/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 22:07:12 by alex              #+#    #+#             */
/*   Updated: 2021/02/06 17:53:58 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"
#include <stdio.h>
t_scene		*define_scene()
{
	t_scene *new;
	
	if (!(new = (t_scene *)malloc(sizeof(t_scene))))
		error_throw(-1);
	new->canvas = NULL;
	new->cameras = NULL;
	//new->objects = NULL;
	new->lights = NULL;
	new->ambient = NULL;
	return (new);
}

int main(int ac, char **av)
{
	t_scene	*scene;
	//char *line = "1 ";
	//double a = atof_modified(&line);
	//printf("%f\n", a);
	scene = define_scene();
	char *line;
	int res;
	int fd = open(av[1], O_RDONLY);
	while((res = get_next_line(fd, &line)) > 0)
	{
		parse_line(line, scene);
		free(line);
	}
	print_cameras(scene);
	print_amb_light(scene);
	return (0);
}