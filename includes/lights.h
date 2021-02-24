/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 14:15:16 by alex              #+#    #+#             */
/*   Updated: 2021/02/24 12:53:16 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTS_H
# define LIGHTS_H

# include "minirt.h"

int					blinn_phong(t_intersect *ans, t_scene *scene);
int 				col_to_int(t_color *color, double *intens);

#endif