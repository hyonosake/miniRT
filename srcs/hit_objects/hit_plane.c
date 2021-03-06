/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 03:11:38 by alex              #+#    #+#             */
/*   Updated: 2021/03/06 23:31:38 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float			plane_intersection(t_plane *plane, float min_t, t_ray *ray)
{
	float		coeffs[2];
	float		res;
	t_vector	tmp;

	coeffs[0] = v_dot_product(&plane->orig, &plane->normal);
	//print_vector(&plane->orig, "pl orig:");
	if (coeffs[0] > 0)
	{
		coeffs[0] *= -1;
		tmp = point_from_vector(&plane->normal, -1);
	}
	else
		tmp = plane->normal;
	coeffs[1] = v_dot_product(&ray->dir, &plane->normal);
	if (ft_fabs(coeffs[1]) < MIN)
		coeffs[1] = MIN;
	res = coeffs[0] / coeffs[1];
	if (res < min_t && res > MIN) 
		return (res);
	return (min_t);
}

t_intersect		*init_plane(t_plane *pl, float res, t_ray *ray, t_vector *col)
{
	t_intersect	*ans;

	if (!(ans = (t_intersect *)malloc(sizeof(t_intersect))))
		error_throw(-1);
	ans->res = res;
	ans->type = OBJ_PLANE;
	ans->color = *col;
	ans->p_inter = point_from_vector(&ray->dir, res);
	//printf("res = %.2f\n", ans->res);
	//print_vector(&ans->p_inter, "inter p:");
	ans->to_cam = point_from_vector(&ray->dir, -1);
	ans->normal = pl->normal;
	//if (v_dot_product(&ans->normal, &ans->to_cam) < 0)
	//{
	//	printf("changer\n");
	//	v_by_scalar(&ans->normal, -1);
	//}
	//v_normalize(&ans->normal);

	return (ans);	
}
