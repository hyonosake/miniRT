/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 03:10:18 by alex              #+#    #+#             */
/*   Updated: 2021/03/06 01:12:34 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float			return_min_positive(float r1, float r2, t_object *sp, float min_t)
{
	sp->type = OBJ_SPHERE;
	if (r1 < 0 && r2 < 0)
		return (min_t);
	if (r1 > 0 && r1 <= r2 && r1 < min_t)
		return (r1);
	else if (r2 > 0 && r2 < r1 && r2 < min_t)
		return (r2);
	return (min_t);
}

float			sphere_intersection(t_ray *ray, t_object *sp, float min_t)
{
	float		coeffs[3];
	float		det;
	t_vector	centers;

	centers = v_sub(&((t_sphere*)sp->content)->orig, &ray->orig);
	coeffs[1] = 2 * v_dot_product(&centers, &ray->dir);
	coeffs[2] = v_dot_product(&centers, &centers) - ((t_sphere*)sp->content)->rsq;
	det = coeffs[1] * coeffs[1] - 4 * coeffs[2];
	if (det < 0)
		return (min_t);
	return (return_min_positive(
		(-coeffs[1] + sqrt(det)) * 0.5,
		(-coeffs[1] - sqrt(det)) * 0.5,
		sp, min_t));
}

t_intersect		*init_sphere(t_object *sphere, float res, t_ray *ray)
{
	t_intersect	*ans;

	if (!(ans = (t_intersect *)malloc(sizeof(t_intersect))))
		error_throw(-1);
	ans->color = sphere->color;
	ans->res = res;
	//printf("HELLOOOOOO\n");
	//printf("res = %.2f\n", ans->res);
	ans->p_inter = point_from_vector(&ray->dir, res);
	//print_vector(&ray->orig, "ray orig:");
	ans->p_inter = v_add(&ans->p_inter, &ray->orig);
	ans->normal = v_sub(&((t_sphere *)sphere->content)->orig, &ans->p_inter);
	v_normalize(&ans->normal);
	//print_vector(&ans->normal, "norm in ans:");
	ans->to_cam = point_from_vector(&ray->dir, -1);
	//print_vector(&ans->p_inter,"p_inter:");
	ans->type = sphere->type;
	//check = v_sub();
	return (ans);
}