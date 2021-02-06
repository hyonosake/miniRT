/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_basis.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 14:06:50 by alex              #+#    #+#             */
/*   Updated: 2021/02/06 20:48:42 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASIS_H
# define BASIS_H

#include "minirt.h"
typedef struct	s_basis
{
	t_vector	*i;
	t_vector	*j;
	t_vector	*k;
}				t_basis;
t_basis			*basis_init(t_vector *forward);
t_vector		*v_from_basis(t_basis *b, double *c);
t_ray			*ray_dir_from_basis(t_camera *cam, t_basis *b, double *c);
t_ray			*new_ray(t_vector *v, t_point *p);

#endif