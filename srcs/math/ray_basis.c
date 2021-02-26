/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_basis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 14:09:11 by alex              #+#    #+#             */
/*   Updated: 2021/02/27 01:47:14 by ffarah           ###   ########.fr       */
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


t_vector		*v_from_basis(t_basis *basis, double a, double b, double c)
{
	t_vector	*new;
	if (!(new = (t_vector *)malloc(sizeof(t_vector))))
		error_throw(-1);
	basis_normalize(basis);
	new->xv = basis->i->xv * a +  basis->j->xv * b +  basis->k->xv * c;
	new->yv = basis->i->yv * a +  basis->j->yv * b +  basis->k->yv * c;
	new->zv = basis->i->zv * a +  basis->j->zv * b +  basis->k->zv * c;
	new->mod = sqrt(v_dot_product(new, new));
	return (new);
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
