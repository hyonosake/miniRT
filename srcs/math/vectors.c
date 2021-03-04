/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 14:18:11 by alex              #+#    #+#             */
/*   Updated: 2021/03/03 13:13:53 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_vector		v_from_values(double x, double y, double z)
{
	t_vector	new;
	
	// if (!(new = (t_vector *)malloc(sizeof(t_vector))))
	// 	error_throw(-1);
	new.xv = x;
	new.yv = y;
	new.zv = z;
	new.mod = sqrt(v_dot_product(&new, &new));
	return (new);
}

double			v_dot_product(t_vector *v1, t_vector *v2)
{
	double result;
	result = v1->xv * v2->xv + v1->yv * v2->yv + v1->zv * v2->zv;
	return (result);
}

t_vector 		v_cross_product(t_vector *v1, t_vector *v2)
{
	t_vector	new;

	new = v_from_values(v1->yv * v2->zv - v1->zv * v2->yv,
						v1->zv * v2->xv - v1->xv * v2->zv,
						v1->xv * v2->yv - v1->yv * v2->xv);
	return (new);
}

t_vector		point_from_vector(t_vector *v1, double d)
{
	t_vector	new;
	new = v_from_values(v1->xv * d,
						v1->yv * d,
						v1->zv * d);
	return (new);
}

void			v_by_scalar(t_vector *v, double d)
{
	v->xv = v->xv * d;
	v->yv = v->yv * d;
	v->zv = v->zv * d;
	v->mod = sqrt(v_dot_product(v, v));
}

