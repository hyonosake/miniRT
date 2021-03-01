/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 03:10:18 by alex              #+#    #+#             */
/*   Updated: 2021/03/01 16:25:27 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

double			return_min_positive(double r1, double r2, t_object *sp, double min_t)
{
	sp->type = OBJ_SPHERE;
	//printf("[%.2f %.2f]\n", r1, r2);
	// if ((r1 > 0 && r2 < 0) || (r1 < 0 && r2 > 0))
	// 	sp->type = INSIDE_OBJ;
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

	centers = *v_sub(((t_sphere*)sp->content)->orig, ray->orig);
	coeffs[1] = 2 * v_dot_product(&centers, ray->dir);
	coeffs[2] = v_dot_product(&centers, &centers) - ((t_sphere*)sp->content)->rsq;
	det = coeffs[1] * coeffs[1] - 4 * coeffs[2];
	if (det < 0)
		return (min_t);
	return (return_min_positive(
		(-coeffs[1] + sqrt(det)) * 0.5,
		(-coeffs[1] - sqrt(det)) * 0.5,
		sp, min_t));
}

t_intersect		*init_sphere(t_object *sphere, double res, t_ray *ray)
{
	t_intersect	*ans;
	t_vector	tmp;

	if (!(ans = (t_intersect *)malloc(sizeof(t_intersect))))
		error_throw(-1);
	ans->color = sphere->color;
	ans->res = res;
	tmp = *point_from_vector(ray->dir, res);
	ans->p_inter = v_add(&tmp, ray->orig);
	ans->to_cam = point_from_vector(ray->dir, -1);
	ans->normal = v_sub(((t_sphere *)sphere->content)->orig, ans->p_inter);
	v_normalize(ans->normal);
	// printf("res = %.2f\n", res);
	//print_vector(ans->p_inter, "inter:");
	//print_vector(ray->orig, "ray orig:");
	//print_vector(ans->normal, "norm:");
	ans->type = sphere->type;
	if (ans->type == INSIDE_OBJ)
		v_by_scalar(ans->normal, -1);
	v_normalize(ans->normal);
	return (ans);
}