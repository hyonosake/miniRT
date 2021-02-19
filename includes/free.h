/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 10:38:45 by alex              #+#    #+#             */
/*   Updated: 2021/02/19 11:47:08 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H
# include "minirt.h"

void			free_ray(t_ray *ray);
void			free_cameras(t_camera *cams);
void			free_lights(t_light *lights);
void			free_plane(t_plane *pl);
void			free_objects(t_object *objs);
void			free_scene(t_scene *scene);

#endif