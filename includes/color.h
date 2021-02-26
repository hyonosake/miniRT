/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 20:30:42 by alex              #+#    #+#             */
/*   Updated: 2021/02/27 00:20:02 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include "minirt.h"
typedef struct		s_color
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
}					t_color;

typedef struct		s_light
{
	int				type;
	t_vector			*orig;
	t_color			*color;
	double 			intensity;
	struct s_light	*next;
}					t_light;

int			bitshift_me_please(t_color *color);
int			intensity_and_color(t_color *color, double intensity);


#endif