/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:23:59 by ffarah            #+#    #+#             */
/*   Updated: 2021/02/26 16:11:57 by ffarah           ###   ########.fr       */
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

typedef struct	s_point
{
	double		xp;
	double		yp;
	double		zp;
	double		mod;
}				t_point;

typedef struct	s_ray
{
	t_vector	*dir;
	t_point		*orig;
}				t_ray;
void			error_throw(int a);
t_vector		*v_from_values(double x, double y, double z);
t_point			*p_from_values(double x, double y, double z);
t_vector		*v_from_p(t_point *p1, t_point *p2);
#endif