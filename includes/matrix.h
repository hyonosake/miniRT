/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 16:10:22 by alex              #+#    #+#             */
/*   Updated: 2021/02/27 02:03:04 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

#include "minirt.h"

double			find_det_three(t_basis *b);
t_basis			*basis_create();
void			basis_free(t_basis *b);
double			find_det_two(double m1, double m2, double m3, double m4);
t_basis			*find_minor_add(t_basis *b);
t_basis			*find_transp_matrix(t_vector *dir);
void			transform_vector(t_basis *trans, t_vector *v);
void			transform_point(t_vector *orig, t_vector *p, t_basis *trans);
#endif