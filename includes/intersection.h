/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 19:23:50 by alex              #+#    #+#             */
/*   Updated: 2021/03/20 02:31:56 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTION_H
# define INTERSECTION_H
# include "minirt.h"

t_intersect		*init_sphere(t_object *sphere, float res, t_ray *ray);
t_intersect		*ray_objects_intersection(t_object *objs, t_ray *ray,
											float min_t);
t_intersect		*init_objects(t_object *object, float res, t_ray *ray);
t_intersect		*init_intersect_struct(t_object *object, float res, t_ray *ray);
void			find_object_normal(t_object *obj, t_intersect *ans, t_ray *ray);
t_vector		create_cy_normal(t_cylinder *cy, t_intersect *ans, t_ray *ray);
float			solve_for_plane_like(t_object *object, t_object *curr_min,
									t_ray *ray, float min_t);
float			triangle_inter(t_trian *tr, t_ray *ray, float min_t);
float			sphere_intersection(t_sphere *sp, t_ray *ray, float min_t);
float			plane_intersection(t_plane *plane, float min_t, t_ray *ray);
float			return_min_positive(float r1, float r2, float min_t);
float			cylinder_intersection(t_cylinder *cy, t_ray *ray, float min_t);
int				disk_intersection(t_disk *disk, t_ray *ray, float res);
int				square_intersection(t_square *sq, t_ray *ray, float res);
#endif
