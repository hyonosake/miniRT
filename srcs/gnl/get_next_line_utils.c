/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 13:15:38 by alex              #+#    #+#             */
/*   Updated: 2021/03/22 12:15:34 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

char				*ft_strjoin(char *orig, char *to_add)
{
	char			*res;
	int				j;
	int				i;

	i = 0;
	j = 0;
	if (!orig && !to_add)
		return (NULL);
	if (!(res = malloc(sizeof(char) * (ft_strlen(orig) +
			ft_strlen(to_add) + 1))))
		return (NULL);
	while (orig && orig[i])
	{
		res[i] = orig[i];
		i++;
	}
	if (orig)
		free(orig);
	while (to_add && to_add[j])
	{
		res[i + j] = to_add[j];
		j++;
	}
	res[i + j] = '\0';
	return (res);
}

int					ft_strlen(char *s)
{
	int				len;

	len = 0;
	if (!s)
		return (0);
	while (s[len] != '\0')
		len++;
	return (len);
}

int					ft_endl_index(char *s)
{
	int				i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char				*ft_before_endl(char *leftover, int endl_index)
{
	char			*res;
	int				i;

	i = 0;
	if (!leftover)
		return (NULL);
	if (endl_index == -1)
		endl_index = ft_strlen(leftover);
	if (!(res = (char*)malloc(sizeof(char) * (endl_index + 1))))
		return (NULL);
	i = 0;
	while (leftover[i] != '\n' && leftover[i])
	{
		res[i] = leftover[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char				*ft_after_endl(char *leftover, int endl_index)
{
	char			*res;
	int				i;

	i = 0;
	if (!leftover)
		return (NULL);
	if (endl_index == -1)
	{
		free(leftover);
		return (NULL);
	}
	endl_index++;
	while (leftover[endl_index + i])
		i++;
	if (!(res = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (leftover[endl_index])
		res[i++] = leftover[endl_index++];
	res[i] = '\0';
	free(leftover);
	return (res);
}
