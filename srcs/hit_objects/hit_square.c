/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_square.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 03:14:03 by alex              #+#    #+#             */
/*   Updated: 2021/02/24 12:23:12 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

double			dots_in_square(t_square *square, int type, t_point *q)
{
	double		res;
	t_vector	*p_q;
	t_vector	*v;

	if (type == 1)
	{
		v = v_from_p(square->p1, square->p2);
		p_q = v_from_p(square->p1, q);
	}
	if (type == 2)
	{
		v = v_from_p(square->p2, square->p3);
		p_q = v_from_p(square->p2, q);
	}
	if (type == 3)
	{
		v = v_from_p(square->p3, square->p4);
		p_q = v_from_p(square->p3, q);
	}
	if (type == 4)
	{
		v = v_from_p(square->p4, square->p1);
		p_q = v_from_p(square->p4, q);
	}
	res = v_dot_product(p_q, v);
	free(p_q);
	free(v);
	return (res);
}

double			check_point_in_square(t_square *square, double min_t, double res, t_point *q)
{

	double		v[4];
	double		check;

	v[0] = dots_in_square(square, 1, q);
	v[1] = dots_in_square(square, 2, q);
	v[2] = dots_in_square(square, 3, q);
	v[3] = dots_in_square(square, 4, q);
	// printf("[%.2f\t,%.2f\t,%.2f\t,%.2f\t]\n", v[0], v[1], v[2], v[3]);
	check = v[0] + v[1] + v[2] + v[3];
	free(square->p1);
	free(square->p2);
	free(square->p3);
	free(square->p4);
	//printf("%.3f = %.3f\n", check, fabs(v[0]) + fabs(v[1]) + fabs(v[2]) + fabs(v[3]));
	if (check != fabs(v[0]) + fabs(v[1]) + fabs(v[2]) + fabs(v[3]))
		return min_t;
	return res;
}

t_point			*square_coord_init(int type, double a, t_basis *for_square)
{
	double		coords[3];


	if (type == 1)
	{
		coords[0] = a / 2;
		coords[1] = a / 2;
	}
	if (type == 2)
	{
		coords[0] = -a / 2;
		coords[1] = a / 2;
	}
	if (type == 3)
	{
		coords[0] = -a / 2;
		coords[1] = -a / 2;
	}
	if (type == 4)
	{
		coords[0] = a / 2;
		coords[1] = -a / 2;
	}
	coords[2] = 0;
	return ((t_point *)v_from_basis(for_square, coords));
}

double			square_intersection(t_square *square, double min_t, t_ray *ray)
{
	t_point		*q;
	t_basis		*for_square;
	double		res;

	res = min_t;
	if ((res = plane_intersection((t_plane *)square, min_t, ray)) < min_t)
	{
		//printf("res = %.3f\n", res);
		for_square = basis_init(square->normal);
		//print_basis(for_square);
		square->p1 = square_coord_init(1, square->a, for_square);
		square->p2 = square_coord_init(2, square->a, for_square);
		square->p3 = square_coord_init(3, square->a, for_square);
		square->p4 = square_coord_init(4, square->a, for_square);
		// printf("\n--------------------------\n");
		// print_point(square->p1);
		// print_point(square->p2);
		// print_point(square->p3);
		// print_point(square->p4);
		// printf("\n--------------------------\n");
		q = (t_point *)v_by_scalar(ray->dir, res);
		basis_free(for_square);
		res = check_point_in_square(square, min_t, res, q);
	}
	return (res);
}