/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 12:34:31 by ffarah            #+#    #+#             */
/*   Updated: 2021/09/14 16:10:06 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_TRACER_H
# define RAY_TRACER_H

# include "minirt.h"

void			*render_scene(void *arg);
void			rotate_x_axis(t_vector *v, float s, float c);
void			rotate_y_axis(t_vector *v, float s, float c);
void			rotate_cam(int key, t_camera *cam, t_scene *scene);
void			transform_wasd(int key, t_camera *cam, t_basis *b);
void			transform_trian(t_trian *tr, t_vector *orig);
#endif
