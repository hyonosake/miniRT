/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 19:23:50 by alex              #+#    #+#             */
/*   Updated: 2021/03/18 15:46:44 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTION_H
# define INTERSECTION_H
# include "minirt.h"

t_intersect		*init_sphere(t_object *sphere, float res, t_ray *ray);
t_intersect		*ray_objects_intersection(t_object *objs, t_ray *ray);
t_intersect		*init_objects(t_object *object, float res, t_ray *ray);
t_intersect		*init_plane(t_plane *pl, float res, t_ray *ray, t_vector *col);
t_intersect		*init_trian(t_trian *tr, float res, t_ray *ray, t_vector *col);
t_intersect		*init_cylinder(t_object *cy, float res, t_ray *ray);
t_intersect		*init_square(t_square *sq, float res,
							t_ray *ray, t_vector *col);
t_intersect		*init_disk(t_disk *disk, float res, t_ray *ray, t_vector *col);

float			triangle_inter(t_trian *tr, t_ray *ray, float min_t);
float			disk_intersection(t_disk *disk, t_ray *ray, float min_t);
float			sphere_intersection(t_sphere *sp, t_ray *ray, float min_t);
float			square_intersection(t_square *sq, t_ray *ray, float min_t);
float			plane_intersection(t_plane *plane, float min_t, t_ray *ray);
float			return_min_positive(float r1, float r2, float min_t);
float			cylinder_intersection(t_cylinder *cy, t_ray *ray, float min_t);
#endif
