/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_square.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 03:14:03 by alex              #+#    #+#             */
/*   Updated: 2021/03/05 09:07:51 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"


double			square_intersection(t_square *sq, t_ray *ray, double min_t)
{
	t_basis		b;
	//t_vector	p[4];
	t_vector	a_new;
	t_vector	q_inter;
	t_vector	a_q;
	double		res;
	double		dot;
	
	res = min_t;
	if ((res = plane_intersection((t_plane *)sq, min_t, ray)) < min_t)
	{
		b = basis_init(&sq->normal);
		q_inter = point_from_vector(&ray->dir, res);
		q_inter = v_add(&q_inter, &ray->orig);
		//q_inter = v_from_basis(&b, &q_inter);
		print_vector(&q_inter, "q_inter");
		a_new = v_add(&a_new, &ray->orig);
		a_new = v_from_basis(&b, &a_new);
		a_q = v_sub(&q_inter, &a_new);
		dot = v_dot_product(&a_q, &b.j);
		if (dot >= - sq->a / 2 && dot <= sq->a / 2)
		{
			dot = v_dot_product(&a_q, &b.i);
			if (dot >= - sq->a / 2 && dot <= sq->a / 2)
				return (res);
		}
	}
	return (res);
}