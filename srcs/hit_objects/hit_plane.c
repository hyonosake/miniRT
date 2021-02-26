/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 03:11:38 by alex              #+#    #+#             */
/*   Updated: 2021/02/26 17:58:28 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

double			plane_intersection(t_plane *plane, double min_t, t_ray *ray)
{
	t_vector	tmp;
	double		coeffs[2];
	double		res;

	tmp = *v_from_p(plane->orig, ray->orig);
	coeffs[0] = v_dot_product(&tmp, plane->normal);
	//printf("c[0] = %.2f\n", coeffs[0]);
	if (coeffs[0] < 0)
	{
		printf("HERE\n");
		tmp = *v_cpy(plane->normal);
		free(plane->normal);
		coeffs[0] *= -1;
		plane->normal = v_by_scalar(&tmp, -1);
	}
	//if (coeffs[0] == 0)
	//	coeffs[0] = 0.00000001;
	//if (coeffs[1] < 0)
	//	coeffs[1] *= -1;
	coeffs[1] = v_dot_product(ray->dir, plane->normal);
	//printf("c[1] = %.2f\n", coeffs[1]);
	if (coeffs[1] == 0)
		coeffs[1] = MIN;
	res = -coeffs[0] / coeffs[1];
	if (res < min_t && res > MIN) 
		return (res);
	//error_throw(-1);
	return (min_t);
}

t_intersect		*init_plane(t_plane *pl, double res, t_ray *ray, t_color *col)
{
	t_intersect	*ans;

	if (!(ans = (t_intersect *)malloc(sizeof(t_intersect))))
		error_throw(-1);
	ans->res = res;
	ans->color = col;
	ans->p_inter = p_from_v(ray->dir, res);
	ans->to_cam = v_by_scalar(ray->dir, -1);
	ans->normal = v_cpy(pl->normal);
	v_normalize(ans->normal);
	v_normalize(ans->to_cam);
	return (ans);	
}
