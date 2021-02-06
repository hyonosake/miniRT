/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 22:07:12 by alex              #+#    #+#             */
/*   Updated: 2021/02/06 21:27:05 by ffarah           ###   ########.fr       */
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
	new->objects = NULL;
	new->lights = NULL;
	new->ambient = NULL;
	return (new);
}

void	parse_input(t_scene *scene, char *name)
{
	char *line;
	int res;
	int	i;

	i = 0;
	while (name[i] != '.' && name[i])
		i++;
	int fd = open(name, O_RDONLY);
	if (!name[i] || (name[i+1] != 'r' && name[i+2] != 't') || fd < 0)
		error_throw(-3);
	while((res = get_next_line(fd, &line)) > 0)
	{
		parse_line(line, scene);
		free(line);
	}
	print_scene(scene);
}
int main(int ac, char **av)
{
	t_scene	*scene;
	scene = define_scene();
	parse_input(scene, av[1]);
	return (0);
}