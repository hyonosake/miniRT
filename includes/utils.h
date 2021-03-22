/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 08:57:34 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/22 12:09:21 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minirt.h"

void			free_ray(t_ray *ray);
void			free_cameras(t_camera *cams);
void			free_lights(t_light *lights);
void			free_plane(t_plane *pl);
void			free_objects(t_object *objs);
int				free_scene(t_scene *scene);
void			print_canvas(t_scene *scene);
void			print_vector(t_vector *v, char *s);
void			print_ray(t_ray *v);
void			print_color(t_vector *color);
void			print_cameras(t_scene *scene);
void			print_amb_light(t_scene *scene);
void			print_lights(t_scene *scene);
void			print_scene(t_scene *scene);
void			print_basis(t_basis *b);
void			mlx_fill(t_scene *scemakne);
void			my_pixel_put(t_mlx *mlx, int x_pix, int y_pix, int col);
void			link_cameras(t_camera *cams);
#endif
