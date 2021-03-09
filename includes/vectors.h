/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:23:59 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/09 09:05:12 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

typedef struct	s_vector
{
	float		xv;
	float		yv;
	float		zv;
	float		mod;
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

t_vector		v_add(t_vector *v1, t_vector *v2);
t_vector		v_sub(t_vector *v1, t_vector *v2);
t_vector		point_from_vector(t_vector *v1, float d);
t_vector		v_from_values(float x, float y, float z);
t_vector		v_from_basis(t_basis *basis, t_vector *c);
t_vector 		v_cross_product(t_vector *v1, t_vector *v2);
t_basis			*basis_create();
t_basis			*find_minor_add(t_basis *b);
t_basis			basis_init(t_vector *forward);
t_basis			*find_transp_matrix(t_vector *dir);
t_ray			new_ray(t_vector *v, t_vector *p);
float			find_det_three(t_basis *b);
float			v_dot_product(t_vector *v1, t_vector *v2);
float			find_det_two(float m1, float m2, float m3, float m4);
void			basis_free(t_basis *b);
void			v_normalize(t_vector *v);
void			basis_normalize(t_basis *b);
void			v_by_scalar(t_vector *v, float d);
void			transform_vector(t_basis *trans, t_vector *v);
void			transform_point(t_vector *orig, t_vector *p, t_basis *trans);
int 			v_isnull(t_vector *v1);
#endif