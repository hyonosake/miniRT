/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 11:48:30 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/18 15:42:38 by ffarah           ###   ########.fr       */
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

void				fill_bmphead(t_bmp_save *new, t_canvas *canv)
{
	new->bmphead[0] = 'B';
	new->bmphead[1] = 'M';
	new->bmphead[2] = (unsigned char)(new->fsize);
	new->bmphead[3] = (unsigned char)(new->fsize >> 8);
	new->bmphead[4] = (unsigned char)(new->fsize >> 16);
	new->bmphead[5] = (unsigned char)(new->fsize >> 24);
	new->bmphead[10] = 54;
	new->bmphead[14] = 40;
	new->bmphead[18] = (unsigned char)(canv->width);
	new->bmphead[19] = (unsigned char)(canv->width >> 8);
	new->bmphead[20] = (unsigned char)(canv->width >> 16);
	new->bmphead[21] = (unsigned char)(canv->width >> 24);
	new->bmphead[22] = (unsigned char)(canv->height);
	new->bmphead[23] = (unsigned char)(canv->height >> 8);
	new->bmphead[24] = (unsigned char)(canv->height >> 16);
	new->bmphead[25] = (unsigned char)(canv->height >> 24);
	new->bmphead[26] = 1;
	new->bmphead[28] = 32;
	new->name = get_name_utc();
}

void				save_to_bmp(t_canvas *canv, t_mlx *mlx)
{
	t_bmp_save		new;

	ft_memset(new.bmphead, BMPHEAD + BMPINFO);
	new.fsize = BMPHEAD + BMPINFO +
		sizeof(int) * canv->height * canv->width;
	fill_bmphead(&new, canv);
	new.fd = open(new.name, O_RDWR | O_CREAT | O_TRUNC, 0666);
	write(new.fd, new.bmphead, BMPINFO + BMPHEAD);
	new.row = canv->height - 1;
	while (new.row >= 0)
	{
		write(new.fd, mlx->addr + new.row * mlx->lsize, canv->width * 4);
		--new.row;
	}
	free(new.name);
	close(new.fd);
}
