/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:23:59 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/03 14:26:27 by alex             ###   ########.fr       */
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
	t_vector	dir;
	t_vector	orig;
}				t_ray;

typedef struct	s_basis
{
	t_vector	i;
	t_vector	j;
	t_vector	k;
}				t_basis;
t_basis			basis_init(t_vector *forward);
void			basis_normalize(t_basis *b);
void			v_from_basis(t_basis *basis, t_vector *v, t_vector *c);
t_ray			new_ray(t_vector *v, t_vector *p);
void			basis_free(t_basis *b);
int 			v_isnull(t_vector *v1);
void			v_normalize(t_vector *v);
t_vector		v_add(t_vector *v1, t_vector *v2);
t_vector		v_sub(t_vector *v1, t_vector *v2);
t_vector		v_from_values(double x, double y, double z);
double			v_dot_product(t_vector *v1, t_vector *v2);
t_vector 		v_cross_product(t_vector *v1, t_vector *v2);
t_vector		point_from_vector(t_vector *v1, double d);
void			v_by_scalar(t_vector *v, double d);
#endif