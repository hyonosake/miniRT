/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_square.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 03:14:03 by alex              #+#    #+#             */
/*   Updated: 2021/02/26 17:42:37 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"


double			check_point_in_square(t_point *intersec, t_square *sq, double min_t, double res)
{
	double		dot;
	int			i;
	t_point		pts[4];
	t_vector	vs[4];
	t_vector	p_q[4];

	i = 0;
	//intersec->xp *= -1;
	//printf("trans_intersec\t");
	//print_point(intersec);
	pts[0] = *p_from_values(sq->a / 2, sq->a / 2, 0);
	pts[1] = *p_from_values(-sq->a / 2, sq->a / 2, 0);
	pts[2] = *p_from_values(-sq->a / 2, -sq->a / 2, 0);
	pts[3] = *p_from_values(sq->a / 2, -sq->a / 2, 0);
	vs[0] = *v_from_p(&pts[0], &pts[1]);
	vs[1] = *v_from_p(&pts[1], &pts[2]);
	vs[2] = *v_from_p(&pts[2], &pts[3]);
	vs[3] = *v_from_p(&pts[3], &pts[0]);
	p_q[0] = *v_from_p(&pts[0], intersec);
	p_q[1] = *v_from_p(&pts[1], intersec);
	p_q[2] = *v_from_p(&pts[2], intersec);
	p_q[3] = *v_from_p(&pts[3], intersec);
	while(i < 4)
	{
		dot = v_dot_product(&vs[i], &p_q[i]);
		if (dot < 0)
		{
			free(intersec);
			return (min_t);
		}
		i++;
	}
	free(intersec);
	return (res);
}


double			square_intersection(t_square *sq, double min_t, t_ray *ray)
{
	t_point		*intersec;
	t_basis		*for_square;
	double		res;
	t_vector	transformed_normal;
	t_point		transformed_orig;
	//t_point		transformed_intersec;
	res = plane_intersection((t_plane *)sq, min_t, ray);
	if (res < min_t && res > MIN)
	{
		//printf("res = %.2f\n", res);
		intersec = (t_point *)v_by_scalar(ray->dir, res);
		//printf("\n---------------------------\n");
		//printf("intersec\t");
		//print_point(intersec);
		for_square = find_transp_matrix(sq->normal);
		transformed_normal = *vector_from_transform(for_square, sq->normal);
		transformed_orig = *point_from_transform(sq->orig, (t_point *)v_cpy((t_vector *)sq->orig), for_square);
		intersec = point_from_transform(sq->orig, intersec, for_square);
		//basis_free(for_square);
		//printf("normal\t\t");
		//print_vector(sq->normal);
		//printf("trans normal\t");
		//print_vector(&transformed_normal);
		//printf("orig\t\t");
		//print_point(sq->orig);
		//printf("trans orig\t");
		//print_point(&transformed_orig);
		//printf("\n---------------------------\n");
		return (check_point_in_square(intersec, sq, min_t, res));
		
	}
	return (min_t);
}