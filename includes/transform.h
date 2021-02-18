/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 16:00:37 by alex              #+#    #+#             */
/*   Updated: 2021/02/18 17:38:15 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSFORM_H
# define TRANSFORM_H
# include "minirt.h"

void			transform_scene(t_scene *scene, t_camera *current_cam);
void			transform_objects(t_scene *scene, t_basis *c_matrix, t_point *c_orig);
void			transform_sphere(t_sphere *sphere, t_basis *c_matrix, t_point *c_orig);
void			transform_plane(t_plane *plane,  t_basis *c_matrix, t_point *c_orig);
void			transform_current_cam(t_camera *current_cam, t_basis *c_matrix);
void			transform_lights(t_light *lights, t_basis *c_matrix, t_point *c_orig);
#endif