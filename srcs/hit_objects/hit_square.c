/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_square.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 03:14:03 by alex              #+#    #+#             */
/*   Updated: 2021/03/17 13:56:34 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float			square_intersection(t_square *sq, t_ray *ray, float min_t)
{
	t_basis		b;
	t_vector	a_p;
	float		res;
	float		dot;

	if ((res = plane_intersection((t_plane *)sq, min_t, ray)) < min_t)
	{
		b = basis_init(&sq->normal);
		basis_normalize(&b);
		a_p = point_from_vector(&ray->dir, res);
		a_p = v_sub(&sq->orig, &a_p);
		dot = ft_fabs(v_dot_product(&a_p, &b.j));
		if (dot <= sq->a * 0.5)
		{
			dot = ft_fabs(v_dot_product(&a_p, &b.i));
			if (dot <= sq->a * 0.5)
				return (res);
		}
	}
	return (min_t);
}

t_intersect		*init_square(t_square *sq, float res, t_ray *ray, t_vector *col)
{
	t_intersect	*ans;

	if (!(ans = (t_intersect *)malloc(sizeof(t_intersect))))
		error_throw(-1);
	ans->res = res;
	ans->type = OBJ_SQUARE;
	ans->color = *col;
	ans->p_inter = point_from_vector(&ray->dir, res);
	ans->p_inter = v_sub(&ray->orig, &ans->p_inter);
	//printf("res = %.2f\n", ans->res);
	//if (ans->p_inter.xv == 0 && ans->p_inter.yv == 0)
	//	print_vector(&ans->p_inter, "disk_p_inter:");
	ans->to_cam = point_from_vector(&ray->dir, -1);
	ans->normal = sq->normal;
	v_normalize(&ans->normal);
	return (ans);	
}