/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 03:10:18 by alex              #+#    #+#             */
/*   Updated: 2021/03/19 23:42:04 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float			sphere_intersection(t_sphere *sp, t_ray *ray, float min_t)
{
	float		coeffs[3];
	float		det;
	float		t[2];
	t_vector	centers;

	centers = v_sub(&ray->orig, &sp->orig);
	coeffs[1] = -2 * v_dot_product(&centers, &ray->dir);
	coeffs[2] = v_dot_product(&centers, &centers) - sp->rsq;
	det = coeffs[1] * coeffs[1] - 4 * coeffs[2];
	if (det < 0)
		return (min_t);
	t[0] = (-coeffs[1] + sqrt(det)) * 0.5;
	t[1] = (-coeffs[1] - sqrt(det)) * 0.5;
	return (define_what_to_ret(t[0], t[1], min_t));
}
