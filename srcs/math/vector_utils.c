/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 14:14:19 by alex              #+#    #+#             */
/*   Updated: 2021/02/09 16:52:24 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

double			v_dot_product(t_vector *v1, t_vector *v2)
{
	double result;
	result = v1->xv * v2->xv + v1->yv * v2->yv + v1->zv * v2->zv;
	return (result);
}

t_vector 		*v_cross_product(t_vector *v1, t_vector *v2)
{
	t_vector	*new;

	new = v_from_values(0,0,0);
	new->xv = v1->yv * v2->zv -	v1->zv * v2->yv;
	new->yv = v1->zv * v2->xv -	v1->xv * v2->zv;
	new->zv = v1->xv * v2->yv -	v1->yv * v2->xv;
	new->mod = sqrt(v_dot_product(new,new));
	return (new);
}

t_vector		*v_by_scalar(t_vector *v1, double d)
{
	t_vector	*new;
	new = v_from_values(0,0,0);
	new->xv = v1->xv * d;
	new->yv = v1->yv * d;
	new->zv = v1->zv * d;
	new->mod = sqrt(v_dot_product(new, new));
	return (new);
}

int 			v_isnull(t_vector *v1)
{
	if (!v1->xv && !v1->yv && !v1->zv)
		return (1);
	return (0);
}

t_vector		*v_cpy(t_vector *v)
{
	return(v_from_values(v->mod, v->yv, v->zv));
}

t_point			*p_cpy(t_point *p)
{
	return (p_from_values(p->xp, p->yp, p->zp));
}

t_point		*p_from_string(char **line)
{
	double	c[3];

	c[0] = atof_modified(line);
	if (**line != ',')
		error_throw(-2);
	++(*line);
	skip_spaces(line);
	c[1] = atof_modified(line);
	if (**line != ',')
		error_throw(-2);
	++(*line);
	skip_spaces(line);
	c[2] = atof_modified(line);
	return(p_from_values(c[0], c[1], c[2]));	
}

t_vector	*v_from_string(char **line)
{
	double	c[3];

	c[0] = atof_modified(line);
	if (**line != ',')
		error_throw(-2);
	++(*line);
	skip_spaces(line);
	c[1] = atof_modified(line);
	if (**line != ',')
		error_throw(-2);
	++(*line);
	skip_spaces(line);
	c[2] = atof_modified(line);
	return(v_from_values(c[0], c[1], c[2]));	
}

void		v_normalize(t_vector *v)
{
	v->xv /= v->mod;
	v->yv /= v->mod;
	v->zv /= v->mod;
	v->mod = sqrt(v_dot_product(v,v));
}

t_point		*p_from_v(t_vector *v, double c)
{
	t_point *new;
	return (p_from_values(v->xv * c, v->yv * c, v->zv * c));
}

t_vector	*v_add(t_vector *v1, t_vector *v2)
{
	t_vector *new;
	
	new = v_from_values(0,0,0);
	new->xv = v1->xv + v2->xv;
	new->yv = v1->yv + v2->yv;
	new->zv = v1->zv + v2->zv;
	new->mod = sqrt(v_dot_product(new,new));
	return (new);
}