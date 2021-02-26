/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 19:23:50 by alex              #+#    #+#             */
/*   Updated: 2021/02/27 01:19:20 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTION_H
# define INTERSECTION_H
# include "minirt.h"
double			return_min_positive(double r1, double r2, t_object *sp, double min_t);
double			sphere_intersection(t_ray *ray, t_object *sp, double min_t);
t_intersect		*init_objects(t_object *object, double res, t_ray *ray);
t_intersect		*init_sphere(t_object *sphere, double res, t_ray *ray);
t_intersect		*init_plane(t_plane *pl, double res, t_ray *ray, t_color *col);
//t_intersect		*init_square(t_square *sq, double res, t_ray *ray, t_color *col);
t_intersect		*ray_objects_intersection(t_object *objs, t_ray *ray);
double			plane_intersection(t_plane *plane, double min_t, t_ray *ray);
double			square_intersection(t_square *square, double min_t, t_ray *ray);
t_vector			*square_coord_init(int type, double a, t_basis *for_square);
double			check_point_in_square(t_vector *intersec, t_square *sq, double min_t, double res);
double			dots_in_square(t_square *square, int type, t_vector *q);
#endif