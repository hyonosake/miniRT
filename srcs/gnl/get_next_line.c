/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 23:39:48 by alex              #+#    #+#             */
/*   Updated: 2021/03/22 12:15:48 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int				get_next_line(int fd, char **line)
{
	static char	*leftover;
	char		*buff;
	int			rv;
	int			endl_index;

	rv = 1;
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (fd < 0 || !line || BUFFER_SIZE <= 0 || !buff)
		return (-1);
	while (rv > 0 && (endl_index = ft_endl_index(leftover)) == -1)
	{
		if ((rv = read(fd, buff, BUFFER_SIZE)) == -1)
			return (ft_free(buff));
		buff[rv] = '\0';
		if (!(leftover = ft_strjoin(leftover, buff)))
			return (ft_free(leftover));
	}
	free(buff);
	if (!(*line = ft_before_endl(leftover, endl_index)))
		return (ft_free(leftover));
	leftover = ft_after_endl(leftover, endl_index);
	return (rv == 0 ? 0 : 1);
}

void			parse_input(t_scene *scene, int ac, char **av)
{
	char		*line;
	int			res;
	int			i;
	int			fd;

	fd = open(av[1], O_RDONLY);
	i = 0;
	if (fd < 0 || (ac < 2 || ac > 3) || !av[1])
		error_throw(INPUT_ERR);
	if (ac == 3 && ft_strcmp(av[2], "--save", 6))
		scene->is_bmp = 1;
	while (av[1][i])
		i++;
	if ((av[1][--i] != 't' || av[1][--i] != 'r' || av[1][--i] != '.'))
		error_throw(INPUT_ERR);
	while ((res = get_next_line(fd, &line)) > 0)
	{
		if (*line == '#')
			continue ;
		parse_line(line, scene);
		free(line);
	}
	parse_line(line, scene);
	free(line);
}

int				ft_free(char *res)
{
	free(res);
	return (-1);
}

int				ft_strcmp(char *s1, char *s2, int n)
{
	int			i;

	i = 0;
	while (s1[i] && i < n)
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}
