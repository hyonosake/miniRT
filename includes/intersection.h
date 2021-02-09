/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 19:23:50 by alex              #+#    #+#             */
/*   Updated: 2021/02/09 17:26:28 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTION_H
# define INTERSECTION_H

double			return_min_positive(double r1, double r2);
double			sphere_intersection(t_ray *ray, t_sphere *sp, double min_t);
t_object		*ray_objects_intersection(t_object *objs, t_ray *ray);
void			loop_through_pixels(void *mlx, void *window, t_scene *scene);

#endif