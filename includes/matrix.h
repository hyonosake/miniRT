/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 16:10:22 by alex              #+#    #+#             */
/*   Updated: 2021/03/06 01:12:20 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

#include "minirt.h"

float			find_det_three(t_basis *b);
t_basis			*basis_create();
void			basis_free(t_basis *b);
float			find_det_two(float m1, float m2, float m3, float m4);
t_basis			*find_minor_add(t_basis *b);
t_basis			*find_transp_matrix(t_vector *dir);
void			transform_vector(t_basis *trans, t_vector *v);
void			transform_point(t_vector *orig, t_vector *p, t_basis *trans);
#endif