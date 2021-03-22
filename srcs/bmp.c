/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 11:48:30 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/22 13:42:49 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void				bitshift_nums(char *line, int num, int start_pos)
{
	(line[start_pos]) = (unsigned char)num;
	++start_pos;
	(line[start_pos]) = (unsigned char)(num >> 8);
	++start_pos;
	(line[start_pos]) = (unsigned char)(num >> 16);
	++start_pos;
	(line[start_pos]) = (unsigned char)(num >> 24);
}

void				fill_bmphead(t_bmp_save *new, t_canvas *canv)
{
	new->bmphead[0] = 'B';
	new->bmphead[1] = 'M';
	bitshift_nums(new->bmphead, new->fsize, 2);
	new->bmphead[10] = BMPHEAD + BMPINFO;
	new->bmphead[14] = BMPINFO;
	bitshift_nums(new->bmphead, canv->width, 18);
	bitshift_nums(new->bmphead, canv->height, 22);
	new->bmphead[26] = 1;
	new->bmphead[28] = 32;
	new->name = get_name_utc();
}

void				save_to_bmp(t_canvas *canv, t_mlx *mlx)
{
	t_bmp_save		new;
	int				i;

	i = 0;
	while (i < BMPHEAD + BMPINFO)
		new.bmphead[i++] = 0;
	new.fsize = BMPHEAD + BMPINFO +
		sizeof(int) * canv->height * canv->width;
	fill_bmphead(&new, canv);
	new.fd = open(new.name, O_RDWR | O_CREAT | O_TRUNC, 438);
	write(new.fd, new.bmphead, BMPINFO + BMPHEAD);
	new.row = canv->height;
	--new.row;
	while (new.row >= 0)
	{
		write(new.fd, mlx->addr + new.row * mlx->lsize, canv->width * 4);
		--new.row;
		i++;
	}
	free(new.name);
	close(new.fd);
}
