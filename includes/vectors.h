/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:23:59 by ffarah            #+#    #+#             */
/*   Updated: 2021/02/27 01:06:58 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

typedef struct	s_vector
{
	double		xv;
	double		yv;
	double		zv;
	double		mod;
}				t_vector;

typedef struct	s_ray
{
	t_vector	*dir;
	t_vector	*orig;
}				t_ray;

int 			v_isnull(t_vector *v1);
t_vector		*copy_vector(t_vector *v);
void			v_normalize(t_vector *v);
t_vector		*v_add(t_vector *v1, t_vector *v2);
t_vector		*v_sub(t_vector *v1, t_vector *v2);
t_vector		*v_from_values(double x, double y, double z);
double			v_dot_product(t_vector *v1, t_vector *v2);
t_vector 		*v_cross_product(t_vector *v1, t_vector *v2);
t_vector		*point_from_vector(t_vector *v1, double d);
void			v_by_scalar(t_vector *v, double d);
#endif