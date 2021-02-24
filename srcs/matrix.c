/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 17:59:34 by alex              #+#    #+#             */
/*   Updated: 2021/02/22 22:55:00 by alex             ###   ########.fr       */
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

t_basis			*find_transp_matrix(t_scene *scene, t_camera *current_cam)
{
	t_basis		*minor;
	t_basis		*b;
	double		det;
	t_basis		*inverse;
	
	b = basis_init(current_cam->dir);
	v_normalize(b->i);
	v_normalize(b->j);
	v_normalize(b->k);
	minor = find_minor_add(b);
	if (!(det = find_det_three(b)))
		return NULL;
	inverse = basis_create();
	//printf("det = %.2f\n", det);
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



t_vector		*vector_from_transform(t_basis *trans, t_vector *v)
{
	t_vector	*new;
	
	new = v_from_values(0,0,0);
	new->xv = trans->i->xv * v->xv + trans->j->xv * v->yv + trans->k->xv * v->zv;
	new->yv = trans->i->yv * v->xv + trans->j->yv * v->yv + trans->k->yv * v->zv;
	new->zv = trans->i->zv * v->xv + trans->j->zv * v->yv + trans->k->zv * v->zv;
	free(v);
	return (new);
}

t_point			*point_from_transform(t_point *cam, t_point *p)
{
	t_point		*tmp;
	t_point		*new;

	tmp = p_from_values(-cam->xp, -cam->yp, -cam->zp);
	new = p_from_values(p->xp + tmp->xp, p->yp + tmp->yp,p->zp + tmp->zp);
	free(tmp);
	free(p);
	return (new);
}