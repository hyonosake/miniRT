/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 14:18:11 by alex              #+#    #+#             */
/*   Updated: 2021/02/18 17:22:27 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_vector		*v_from_values(double x, double y, double z)
{
	t_vector	*new;
	
	if (!(new = (t_vector *)malloc(sizeof(t_vector))))
		error_throw(-1);
	new->xv = x;
	new->yv = y;
	new->zv = z;
	new->mod = sqrt(v_dot_product(new, new));
	return (new);
}

t_point			*p_from_values(double x, double y, double z)
{
	t_point		*new;
	
	if (!(new = (t_point *)malloc(sizeof(t_point))))
		error_throw(-1);
	new->xp = x;
	new->yp = y;
	new->zp = z;
	return (new);
}

t_vector		*v_from_p(t_point *p1, t_point *p2)
{
	t_vector	*new;
	
	new = v_from_values(0,0,0);
	new->xv = p2->xp - p1->xp;
	new->yv = p2->yp - p1->yp;
	new->zv = p2->zp - p1->zp;
	new->mod = sqrt(v_dot_product(new, new));
	return (new);
}