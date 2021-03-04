/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_basis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 14:09:11 by alex              #+#    #+#             */
/*   Updated: 2021/03/04 00:52:15 by alex             ###   ########.fr       */
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
		printf("v_isnull\n");
		up = v_from_values(0, 0, -1);
		b.i = v_cross_product(&up, forward);
	}
	b.j = v_cross_product(forward, &b.i);
	basis_normalize(&b);
	// b.i.mod = sqrt(v_dot_product(&b.i, &b.i));
	// b.j.mod = sqrt(v_dot_product(&b.j, &b.j));
	// b.k.mod = sqrt(v_dot_product(&b.k, &b.k));
	return (b);
}


void			v_from_basis(t_basis *basis, t_vector *v, t_vector *c)
{
	//basis_normalize(basis);
	v->xv = basis->i.xv * c->xv +  basis->j.xv * c->yv +  basis->k.xv * c->zv;
	v->yv = basis->i.yv * c->xv +  basis->j.yv * c->yv +  basis->k.yv * c->zv;
	v->zv = basis->i.zv * c->xv +  basis->j.zv * c->yv +  basis->k.zv * c->zv;
	v->mod = sqrt(v_dot_product(v, v));
	v_normalize(v);
}

t_ray		new_ray(t_vector *v, t_vector *p)
{
	t_ray	new;
	// if (!(new = (t_ray *)malloc(sizeof(t_ray))))
	// 	error_throw(-1);
	new.orig = *p;
	new.dir = *v;
	return (new);
}

// t_ray		ray_from_basis(t_vector *cam_orig, t_basis *b)
// {
// 	t_ray	new;
// 	// if (!(new = (t_ray *)malloc(sizeof(t_ray))))
// 	// 	error_throw(-1);
// 	// new.orig = ;
// 	// new.dir = v;
// 	return (new);
// }