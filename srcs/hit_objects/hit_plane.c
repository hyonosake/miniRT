/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 03:11:38 by alex              #+#    #+#             */
/*   Updated: 2021/03/15 16:47:46 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float			plane_intersection(t_plane *plane, float min_t, t_ray *ray)
{
	t_vector	centers;
	float		dots[2];
	float		ret_val;

	centers = v_sub(&ray->orig, &plane->orig);
	if (v_dot_product(&ray->dir, &plane->normal) > 0)
		v_by_scalar(&plane->normal, -1);
	//print_vector(&centers, "centers:");
	dots[0] = v_dot_product(&plane->normal, &centers);
	//printf("dots[0] = %.10f\n", dots[0]);
	// if (dots[0] > MIN)
	// 	dots[0] *= -1;
	dots[1] = v_dot_product(&ray->dir, &plane->normal);
	//printf("dots[1]  =%.3f\n", dots[1]);
	if (dots[1] == 0)
		dots[1] = MIN;
	ret_val = dots[0] / dots[1];
	if (ret_val > min_t || ret_val < MIN)
		ret_val = min_t;
	//printf("ret_val:%.2f\n", ret_val);
	return (ret_val);
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
	v_normalize(&ans->normal);
	//if (v_dot_product(&ans->normal, &ans->to_cam) < 0)
	//{
	//	printf("changer\n");
	//	v_by_scalar(&ans->normal, -1);
	//}
	return (ans);	
}
