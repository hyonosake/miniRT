/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmpmake.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 12:34:38 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/22 13:42:14 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMPMAKE_H
# define BMPMAKE_H
# include "minirt.h"

typedef struct	s_bmp_save
{
	char		bmphead[BMPHEAD + BMPINFO];
	char		*name;
	int			fsize;
	int			fd;
	int			row;
}				t_bmp_save;

void			fill_bmphead(t_bmp_save *new, t_canvas *canv);
void			save_to_bmp(t_canvas *canv, t_mlx *mlx);
void			ft_memset(void *ptr, int n);
char			*get_name_utc();
char			*add_bmp_in_filename(char *utc);
void			bitshift_nums(char *line, int num, int start_pos);

#endif
