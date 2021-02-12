/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 14:15:16 by alex              #+#    #+#             */
/*   Updated: 2021/02/11 20:59:14 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTS_H
# define LIGHTS_H

#include "minirt.h"

typedef struct		s_light
{
	t_point			*orig;
	t_color			*color;
	double 			intensity;
	struct s_light	*next;
}					t_light;


#endif