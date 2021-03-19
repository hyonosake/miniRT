/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_square.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 03:14:03 by alex              #+#    #+#             */
/*   Updated: 2021/03/19 15:20:23 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int				square_intersection(t_square *sq, t_ray *ray, float res)
{
	t_basis		b;
	t_vector	a_p;
	float		dot;

	b = basis_init(&sq->normal);
	basis_normalize(&b);
	a_p = point_from_vector(&ray->dir, res);
	a_p = v_sub(&sq->orig, &a_p);
	dot = ft_fabs(v_dot_product(&a_p, &b.j));
	if (dot <= sq->ahalf)
	{
		dot = ft_fabs(v_dot_product(&a_p, &b.i));
		if (dot <= sq->ahalf)
			return (1);
	}
	return (0);
}

t_intersect		*init_square(t_square *sq, float res, t_ray *ray, t_vector *col)
{
	t_intersect	*ans;

	if (!(ans = (t_intersect *)malloc(sizeof(t_intersect))))
		error_throw(MALLOC_ERR);
	ans->res = res;
	ans->type = SQUARE;
	ans->color = *col;
	ans->p_inter = point_from_vector(&ray->dir, res);
	ans->p_inter = v_sub(&ray->orig, &ans->p_inter);
	ans->to_cam = point_from_vector(&ray->dir, -1);
	ans->normal = sq->normal;
	v_normalize(&ans->normal);
	return (ans);
}
