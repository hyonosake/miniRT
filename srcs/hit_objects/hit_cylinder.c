/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 09:22:18 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/22 11:50:13 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_vector		create_cy_normal(t_cylinder *cy, t_intersect *ans, t_ray *ray)
{
	t_vector	tau;
	t_vector	ap;
	t_vector	op;

	op = v_sub(&ray->orig, &ans->p_inter);
	ap = v_sub(&cy->orig, &op);
	v_normalize(&ap);
	tau = v_cross_product(&cy->axis, &ap);
	return (v_cross_product(&cy->axis, &tau));
}

float			correct_solution(t_cylinder *cy, float min_t,
								t_ray *ray, t_vector *co)
{
	float		dots[2];
	t_vector	ap;

	ap = point_from_vector(&ray->dir, cy->t[0]);
	dots[0] = ft_fabs(v_dot_product(&cy->axis, &ap) +
		v_dot_product(co, &cy->axis));
	ap = point_from_vector(&ray->dir, cy->t[1]);
	dots[1] = ft_fabs(v_dot_product(&cy->axis, &ap) +
		v_dot_product(co, &cy->axis));
	if (dots[0] > cy->lhalf)
		cy->t[0] = -1;
	if (dots[1] > cy->lhalf)
		cy->t[1] = -1;
	return (define_what_to_ret(cy->t[0], cy->t[1], min_t));
}

float			cylinder_intersection(t_cylinder *cy, t_ray *ray, float min_t)
{
	float		coeffs[3];
	float		ret_val;
	float		det;
	t_vector	co;

	co = v_sub(&cy->orig, &ray->orig);
	coeffs[0] = v_dot_product(&ray->dir, &cy->axis) *
		v_dot_product(&ray->dir, &cy->axis) - 1;
	coeffs[1] = 2 * (v_dot_product(&co, &cy->axis) *
		v_dot_product(&ray->dir, &cy->axis) - v_dot_product(&ray->dir, &co));
	coeffs[2] = v_dot_product(&co, &cy->axis) *
		v_dot_product(&co, &cy->axis) + cy->rsq - co.mod * co.mod;
	det = coeffs[1] * coeffs[1] - 4 * coeffs[0] * coeffs[2];
	if (det < 0)
		return (min_t);
	cy->t[0] = (-coeffs[1] - sqrt(det)) / (2 * coeffs[0]);
	cy->t[1] = (-coeffs[1] + sqrt(det)) / (2 * coeffs[0]);
	if ((cy->t[0] < MIN && cy->t[1] < MIN) ||
		(cy->t[0] > min_t && cy->t[1] > min_t))
		return (min_t);
	ret_val = correct_solution(cy, min_t, ray, &co);
	return (ret_val);
}
