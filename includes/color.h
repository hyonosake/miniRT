/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 20:30:42 by alex              #+#    #+#             */
/*   Updated: 2021/02/08 19:24:40 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

typedef struct		s_color
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
}					t_color;
int			bitshift_me_please(t_color *color);
int			intensity_and_color(t_color *color, double intensity);


#endif