/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 17:59:34 by alex              #+#    #+#             */
/*   Updated: 2021/03/01 20:44:13 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"



double			find_det_three(t_basis *b)
{
	double		res;

	res = b->i->xv * b->j->yv * b->k->zv +
			b->k->xv * b->j->zv * b->i->yv +
			b->j->xv * b->k->yv * b->i->zv -
			b->k->xv * b->j->yv * b->i->zv -
			b->i->xv * b->k->yv * b->j->zv -
			b->j->xv * b->i->yv * b->k->zv; 
	return res;
}

t_basis			*basis_create()
{
	t_basis		*new;
	
	if (!(new = (t_basis *)malloc(sizeof(t_basis))))
		error_throw(-1);
	new->i = v_from_values(0,0,0);
	new->j = v_from_values(0,0,0);
	new->k = v_from_values(0,0,0);
	return (new);
}

void			basis_free(t_basis *b)
{
	free(b->i);
	free(b->j);
	free(b->k);
	free(b);
}

double			find_det_two(double m1, double m2, double m3, double m4)
{
	double		res;
	res = m1 * m2 - m3 * m4;
	return (res);
}

t_basis			*find_minor_add(t_basis *b)
{
	t_basis		*new;
	
	new = basis_create();
	new->i->xv = b->j->yv * b->k->zv - b->j->zv * b->k->yv;
	new->i->yv = b->j->xv * b->k->zv - b->j->zv * b->k->xv;
	new->i->zv = b->j->xv * b->k->yv - b->j->yv * b->k->xv;
	
	new->j->xv = b->i->yv * b->k->zv - b->i->zv * b->k->yv;
	new->j->yv = b->i->xv * b->k->zv - b->i->zv * b->k->xv;
	new->j->zv = b->i->xv * b->k->yv - b->i->yv * b->k->xv;

	new->k->xv = b->i->yv * b->j->zv - b->i->zv * b->j->yv;
	new->k->yv = b->i->xv * b->j->zv - b->i->zv * b->j->xv;
	new->k->zv = b->i->xv * b->j->yv - b->i->yv * b->j->xv;
	
	new->i->yv *= -1;
	new->j->xv *= -1;
	new->j->zv *= -1;
	new->k->yv *= -1;
	return (new);
}

t_basis			*find_transp_matrix(t_vector *dir)
{
	t_basis		*minor;
	t_basis		*b;
	double		det;
	t_basis		*inverse;
	
	b = basis_init(dir);
	basis_normalize(b);
	minor = find_minor_add(b);
	if (!(det = find_det_three(b)))
		return NULL;
	inverse = basis_create();
	inverse->i->xv = minor->i->xv;
	inverse->i->yv = minor->j->xv;
	inverse->i->zv = minor->k->xv;

	inverse->j->xv = minor->i->yv;
	inverse->j->yv = minor->j->yv;
	inverse->j->zv = minor->k->yv;

	inverse->k->xv = minor->i->zv;
	inverse->k->yv = minor->j->zv;
	inverse->k->zv = minor->k->zv;
	basis_free(minor);
	basis_free(b);
	return (inverse);
}



void			transform_vector(t_basis *trans, t_vector *v)
{
	t_vector	c;
	c = *copy_vector(v);
	v->xv = trans->i->xv * c.xv + trans->j->xv * c.yv + trans->k->xv * c.zv;
	v->yv = trans->i->yv * c.xv + trans->j->yv * c.yv + trans->k->yv * c.zv;
	v->zv = trans->i->zv * c.xv + trans->j->zv * c.yv + trans->k->zv * c.zv;
	v_normalize(v);
}

void			transform_point(t_vector *orig, t_vector *changed, t_basis *trans)
{
	t_vector	c;
	t_vector	f;
	f = *copy_vector(changed);
	c = *v_sub(orig, &f);
	//print_vector(trans->i,"nvm");
	//print_vector(&c, "coord transf");
	changed->xv = trans->i->xv * c.xv + trans->j->xv * c.yv + trans->k->xv * c.zv;
	changed->yv = trans->i->yv * c.xv + trans->j->yv * c.yv + trans->k->yv * c.zv;
	changed->zv = trans->i->zv * c.xv + trans->j->zv * c.yv + trans->k->zv * c.zv;
	
}