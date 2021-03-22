/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 12:56:34 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/22 12:57:22 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

char				*add_bmp_in_filename(char *utc)
{
	char			*res;
	int				i;

	if (!(res = malloc(sizeof(char) * (ft_strlen(utc) + 5))))
		error_throw(MALLOC_ERR);
	i = 0;
	while (utc[i])
	{
		res[i] = utc[i];
		i++;
	}
	res[--i] = '.';
	res[++i] = 'b';
	res[++i] = 'm';
	res[++i] = 'p';
	res[++i] = 0;
	return (res);
}

char				*get_name_utc(void)
{
	struct tm		time_struct;
	time_t			curr_time;
	char			*time_str;

	curr_time = time(&curr_time);
	time_struct = *gmtime(&curr_time);
	time_str = asctime(&time_struct);
	return (add_bmp_in_filename(time_str));
}

void				ft_memset(void *ptr, int n)
{
	unsigned char	*ch;
	int				i;

	i = 0;
	ch = (unsigned char *)ptr;
	while (i < n)
	{
		ch[i] = 0;
		i++;
	}
}
