/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 19:23:50 by alex              #+#    #+#             */
/*   Updated: 2021/03/06 01:12:20 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTION_H
# define INTERSECTION_H
# include "minirt.h"
float			return_min_positive(float r1, float r2, t_object *sp, float min_t);
float			sphere_intersection(t_ray *ray, t_object *sp, float min_t);
t_intersect		*init_objects(t_object *object, float res, t_ray *ray);
t_intersect		*init_sphere(t_object *sphere, float res, t_ray *ray);
t_intersect		*init_plane(t_plane *pl, float res, t_ray *ray, t_vector *col);
t_intersect		*init_trian(t_trian *tr, float res, t_ray *ray, t_vector *col);
t_intersect		*ray_objects_intersection(t_object *objs, t_ray *ray);
float			plane_intersection(t_plane *plane, float min_t, t_ray *ray);
float			square_intersection(t_square *sq, t_ray *ray, float min_t);
float			triangle_inter(t_trian *tr, t_ray *ray, float min_t);
#endif