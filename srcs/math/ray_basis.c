/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_basis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 14:09:11 by alex              #+#    #+#             */
/*   Updated: 2021/03/15 10:27:54 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void			basis_normalize(t_basis *b)
{
	v_normalize(&b->i);
	v_normalize(&b->j);
	v_normalize(&b->k);
}

t_basis			basis_init(t_vector *forward)
{
	t_basis		b;
	t_vector	up;

	up = v_from_values(0, 1, 0);
	b.i = v_cross_product(&up, forward);
	b.k = *forward;
	if (v_isnull(&b.i))
	{
		//printf("v_isnull\n");
		up = v_from_values(0, 0, -1);
		b.i = v_cross_product(&up, forward);
	}
	b.j = v_cross_product(forward, &b.i);
	basis_normalize(&b);
	return (b);
}


t_vector		v_from_basis(t_basis *basis, t_vector *c)
{
	t_vector	v;
	//basis_normalize(basis);
	v.xv = basis->i.xv * c->xv +  basis->j.xv * c->yv +  basis->k.xv * c->zv;
	v.yv = basis->i.yv * c->xv +  basis->j.yv * c->yv +  basis->k.yv * c->zv;
	v.zv = basis->i.zv * c->xv +  basis->j.zv * c->yv +  basis->k.zv * c->zv;
	v.mod = sqrt(v_dot_product(&v, &v));
	//v_normalize(&v);
	return (v);
}

t_ray		new_ray(t_vector *v, t_vector *p)
{
	t_ray	new;
	new.orig = *p;
	new.dir = *v;
	return (new);
}