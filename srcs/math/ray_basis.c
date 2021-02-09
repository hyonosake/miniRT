/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_basis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 14:09:11 by alex              #+#    #+#             */
/*   Updated: 2021/02/09 16:52:21 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_basis			*basis_init(t_vector *forward)
{
	t_basis		*c_basis;
	t_vector	*up;

	if (!(c_basis = (t_basis *)malloc(sizeof(t_basis))))
		error_throw(-1);
	up = v_from_values(0, 1, 0);
	c_basis->k = forward;
	c_basis->i = v_cross_product(up, forward);
	if (v_isnull(c_basis->i))
	{
		free(c_basis->i);
		free(up);
		up = v_from_values(1, 0, 0);
		c_basis->i = v_cross_product(up, forward);
	}
	c_basis->j = v_cross_product(forward, c_basis->i);
	free(up);
	return (c_basis);
}


t_vector		*v_from_basis(t_basis *b, double *c)
{
	t_vector	*new;
	if (!(new = (t_vector *)malloc(sizeof(t_vector))))
		error_throw(-1);
	//printf("[%.3f %.3f %.3f]\n",c[0],c[1],c[2]);
	new->xv = b->i->xv * c[0] +  b->j->xv * c[1] +  b->k->xv * c[2];
	new->yv = b->i->yv * c[0] +  b->j->yv * c[1] +  b->k->yv * c[2];
	new->zv = b->i->zv * c[0] +  b->j->zv * c[1] +  b->k->zv * c[2];
	new->mod = sqrt(v_dot_product(new, new));
	return (new);
}

t_ray		*ray_dir_from_basis(t_camera *cam, t_basis *b, double *c)
{
	t_ray		*new;
	if (!(new = (t_ray *)malloc(sizeof(t_ray))))
		error_throw(-1);
	new->dir = v_from_basis(b, c);
	new->orig = p_cpy(cam->orig);
	v_normalize(new->dir);
	return (new);
}

t_ray		*new_ray(t_vector *v, t_point *p)
{
	t_ray	*new;
	if (!(new = (t_ray *)malloc(sizeof(t_ray))))
		error_throw(-1);
	new->orig = p;
	new->dir = v;
	return (new);
}

