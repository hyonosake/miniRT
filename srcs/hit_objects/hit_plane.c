/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 03:11:38 by alex              #+#    #+#             */
/*   Updated: 2021/03/09 12:53:10 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float			plane_intersection(t_plane *plane, float min_t, t_ray *ray)
{
	t_vector	tmp;


	float denom = v_dot_product(&plane->normal, &ray->dir);
	//if (ft_fabs(denom) > MIN)
	//{
		tmp = v_sub(&ray->orig, &plane->orig);
		float t = v_dot_product(&tmp, &plane->normal) / denom;
		if (t > 0 && t < min_t)
			return t;
		return (min_t);
		
	//}
	return (min_t);
	//float		coeffs[2];
	//float		res;
	//tmp = v_sub(&ray->orig, &plane->orig);
	//coeffs[0] = v_dot_product(&tmp, &plane->normal);
	//tmp = plane->normal;
	//coeffs[1] = v_dot_product(&ray->dir, &plane->normal);
	//if (coeffs[1] > 0)
	//	return (min_t);
	//if (coeffs[1] == 0)
	//	coeffs[1] = MIN;
	//res = coeffs[0] / coeffs[1];
	////printf("res = %.2f\n", res);
	//if (res < min_t && res > MIN) 
	//	return (res);
	//return (min_t);
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
