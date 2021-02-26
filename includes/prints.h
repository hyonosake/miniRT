/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 01:16:48 by ffarah            #+#    #+#             */
/*   Updated: 2021/02/27 01:28:59 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTS_H
# define PRINTS_H
# include "minirt.h"
void	print_canvas(t_scene *scene);
void	print_vector(t_vector *v, char *s);
void	print_ray(t_ray *v);
void	print_color(t_color *color);
void	print_cameras(t_scene *scene);
void	print_amb_light(t_scene *scene);
void	print_lights(t_scene *scene);
void	print_objects(t_scene *scene);
void	print_scene(t_scene *scene);
void	print_basis(t_basis *b);
#endif