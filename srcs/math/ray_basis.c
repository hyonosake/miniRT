/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_basis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 14:09:11 by alex              #+#    #+#             */
/*   Updated: 2021/03/01 08:53:45 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void			basis_normalize(t_basis *b)
{
	v_normalize(b->i);
	v_normalize(b->j);
	v_normalize(b->k);
}

t_basis			*basis_init(t_vector *forward)
{
	t_basis		*c_basis;
	t_vector	up;

	if (!(c_basis = (t_basis *)malloc(sizeof(t_basis))))
		error_throw(-1);
	up = *v_from_values(0, 1, 0);
	c_basis->k = copy_vector(forward);
	c_basis->i = v_cross_product(&up, forward);
	if (v_isnull(c_basis->i))
	{
		free(c_basis->i);
		up = *v_from_values(1, 0, 0);
		c_basis->i = v_cross_product(&up, forward);
	}
	c_basis->j = v_cross_product(forward, c_basis->i);
	return (c_basis);
}


void			v_from_basis(t_basis *basis, t_vector *v, double *c)
{
	basis_normalize(basis);
	v->xv = basis->i->xv * c[0] +  basis->j->xv * c[1] +  basis->k->xv * c[2];
	v->yv = basis->i->yv * c[0] +  basis->j->yv * c[1] +  basis->k->yv * c[2];
	v->zv = basis->i->zv * c[0] +  basis->j->zv * c[1] +  basis->k->zv * c[2];
	v->mod = sqrt(v_dot_product(v, v));
	v_normalize(v);
}

t_ray		*new_ray(t_vector *v, t_vector *p)
{
	t_ray	*new;
	if (!(new = (t_ray *)malloc(sizeof(t_ray))))
		error_throw(-1);
	new->orig = p;
	new->dir = v;
	return (new);
}
