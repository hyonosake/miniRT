/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_square.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 03:14:03 by alex              #+#    #+#             */
/*   Updated: 2021/03/05 14:18:30 by alex             ###   ########.fr       */
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
	//t_vector	cam; 
	double		res;
	double		dot;
	
	res = min_t;
	if ((res = plane_intersection((t_plane *)sq, min_t, ray)) < min_t)
	{
		b = basis_init(&sq->normal);
		// print_vector(&a_new, "a_new with cum\t");
		q_inter = point_from_vector(&ray->dir, res);
		//print_vector(&q_inter, "q_inter bfore\t");
		//q_inter = v_add(&q_inter, &ray->orig);
		//print_vector(&q_inter, "q_inter_with_cam");
		//print_vector(&sq->orig, "sq orig\t\t");
		a_new = v_sub(&ray->orig, &sq->orig);
		//print_vector(&a_new, "a_new with cum\t");

		a_new = v_from_basis(&b, &a_new);
		q_inter = v_from_basis(&b, &q_inter);
		//print_vector(&a_new, "anuw\t");
		//print_vector(&q_inter, "pinter\t");
		q_inter = v_add(&a_new, &q_inter);
		a_new = v_add(&a_new, &a_new);
		a_q = v_sub(&a_new, &q_inter);
		//print_vector(&a_q, "aqula\t");
		dot = v_dot_product(&a_q, &b.j);
		if (dot >= -sq->a / 2 && dot <= sq->a / 2)
		{
			dot = v_dot_product(&a_q, &b.i);
			if (dot >= -sq->a / 2 && dot <= sq->a / 2)
				return (res);
		}
	}
	return (res);
}