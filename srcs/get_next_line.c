/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 23:39:48 by alex              #+#    #+#             */
/*   Updated: 2021/02/06 02:34:43 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

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
	if (!(*line = ft_line_fill(leftover, endl_index)))
		return (ft_free(leftover));
	leftover = ft_make_left_pretty(leftover, endl_index);
	return (rv == 0 ? 0 : 1);
}

int				ft_free(char *res)
{
	free(res);
	return (-1);
}
