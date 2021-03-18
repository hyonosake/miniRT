/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 14:14:19 by alex              #+#    #+#             */
/*   Updated: 2021/03/18 16:10:14 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int				v_isnull(t_vector *v1)
{
	if (!v1->xv && !v1->yv && !v1->zv)
		return (1);
	return (0);
}

void			v_normalize(t_vector *v)
{
	v->xv /= v->mod;
	v->yv /= v->mod;
	v->zv /= v->mod;
	v->mod = 1;
}

t_vector		v_add(t_vector *v1, t_vector *v2)
{
	return (v_from_values(v2->xv + v1->xv,
							v2->yv + v1->yv,
							v2->zv + v1->zv));
}

t_vector		v_sub(t_vector *v1, t_vector *v2)
{
	return (v_from_values(v2->xv - v1->xv,
						v2->yv - v1->yv,
						v2->zv - v1->zv));
}

t_vector		color_multiply(t_vector *v1, t_vector *v2, double k)
{
	t_vector	new;

	new.xv = v1->xv * v2->xv * k;
	new.yv = v1->yv * v2->yv * k;
	new.zv = v1->zv * v2->zv * k;
	new.mod = 0;
	return (new);
}
