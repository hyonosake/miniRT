/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 19:23:50 by alex              #+#    #+#             */
/*   Updated: 2021/02/08 19:26:58 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTION_H
# define INTERSECTION_H

double		return_min_positive(double r1, double r2);
void				sphere_intersection(t_ray *ray, t_sphere *sp, t_trace *ans, t_color *color);
t_trace 		*ray_objects_intersection(t_object *objs, t_ray *ray);
void			loop_through_pixels(void *mlx, void *window, t_scene *scene);

#endif