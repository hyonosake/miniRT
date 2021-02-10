/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 19:23:50 by alex              #+#    #+#             */
/*   Updated: 2021/02/10 14:29:37 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTION_H
# define INTERSECTION_H

double		return_min_positive(double r1, double r2, double min_t);
double		sphere_intersection(t_ray *ray, t_sphere *sp, double min_t);
t_intersect		*init_objects(t_object *object, double res, t_ray *ray);
t_intersect		*ray_objects_intersection(t_object *objs, t_ray *ray);
double			plane_intersection(t_plane *plane, double min_t, t_ray *ray);

#endif