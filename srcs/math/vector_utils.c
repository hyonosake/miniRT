/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 14:14:19 by alex              #+#    #+#             */
/*   Updated: 2021/02/27 01:18:42 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int 			v_isnull(t_vector *v1)
{
	if (!v1->xv && !v1->yv && !v1->zv)
		return (1);
	return (0);
}

t_vector		*copy_vector(t_vector *v)
{
	return(v_from_values(v->xv, v->yv, v->zv));
}

void			v_normalize(t_vector *v)
{
	v->xv /= v->mod;
	v->yv /= v->mod;
	v->zv /= v->mod;
	v->mod = 1;
}

t_vector		*v_add(t_vector *v1, t_vector *v2)
{
	t_vector	*new;
	
	new = v_from_values(0,0,0);
	new->xv = v1->xv + v2->xv;
	new->yv = v1->yv + v2->yv;
	new->zv = v1->zv + v2->zv;
	new->mod = sqrt(v_dot_product(new,new));
	return (new);
}

t_vector		*v_sub(t_vector *v1, t_vector *v2)
{
	t_vector	*new;
	
	new = v_from_values(0,0,0);
	new->xv = v2->xv - v1->xv;
	new->yv = v2->yv - v1->yv;
	new->zv = v2->zv - v1->zv;
	new->mod = sqrt(v_dot_product(new,new));
	return (new);
}