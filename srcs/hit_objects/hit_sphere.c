/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 03:10:18 by alex              #+#    #+#             */
/*   Updated: 2021/02/27 01:29:18 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

double			return_min_positive(double r1, double r2, t_object *sp, double min_t)
{
	if ((r1 > 0 && r2 < 0) || (r1 < 0 && r2 > 0))
		sp->type = INSIDE_OBJ;
	if (r1 < 0 && r2 < 0)
		return (min_t);
	if (r1 > 0 && r1 <= r2 && r1 < min_t)
		return (r1);
	else if (r2 > 0 && r2 < r1 && r2 < min_t)
		return (r2);
	return (min_t);
}

double			sphere_intersection(t_ray *ray, t_object *sp, double min_t)
{
	double		coeffs[3];
	double		det;
	t_vector	centers;

	print_vector(((t_sphere*)sp->content)->orig, "I am here and point is:\n");
	centers = *v_sub(((t_sphere*)sp->content)->orig, ray->orig);
	coeffs[0] = 1;
	coeffs[1] = 2 * v_dot_product(&centers, ray->dir);
	coeffs[2] = centers.mod - ((t_sphere*)sp->content)->rsq;
	det = coeffs[1] * coeffs[1] - 4 * coeffs[0] * coeffs[2];
	if (det < 0)
		return (min_t);
	return (return_min_positive(
		(-coeffs[1] + sqrt(det)) / (2 * coeffs[0]),
		(-coeffs[1] - sqrt(det)) / (2 * coeffs[0]),
		sp, min_t));
}

t_intersect		*init_sphere(t_object *sphere, double res, t_ray *ray)
{
	t_intersect	*ans;

	if (!(ans = (t_intersect *)malloc(sizeof(t_intersect))))
		error_throw(-1);
	ans->color = sphere->color;
	ans->res = res;
	ans->p_inter = point_from_vector(ray->dir, res);
	ans->to_cam = point_from_vector(ray->dir, -1);
	ans->normal = v_sub(((t_sphere *)sphere)->orig, ans->p_inter);
	ans->type = sphere->type;
	if (ans->type == INSIDE_OBJ)
		v_by_scalar(ans->normal, -1);
	v_normalize(ans->normal);
	return (ans);
}