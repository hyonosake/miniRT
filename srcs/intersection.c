///* ************************************************************************** */
///*                                                                            */
///*                                                        :::      ::::::::   */
///*   intersection.c                                     :+:      :+:    :+:   */
///*                                                    +:+ +:+         +:+     */
///*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
///*                                                +#+#+#+#+#+   +#+           */
///*   Created: 2021/02/08 19:25:48 by alex              #+#    #+#             */
///*   Updated: 2021/02/09 17:38:10 by ffarah           ###   ########.fr       */
///*                                                                            */
///* ************************************************************************** */

#include "../includes/minirt.h"


double		return_min_positive(double r1, double r2, double min_t)
{
	if (r1 < 0 || r2 < 0)
		return (min_t);
	if (r1 > 0 && r1 <= r2)
		return (r1);
	else if (r2 > 0 && r2 < r1)
		return (r2);
	return (min_t);
}

double		sphere_intersection(t_ray *ray, t_sphere *sp, double min_t)
{
	double	coeffs[3];
	double	det;
	double	ret_val;
	t_vector *centers;
	
	centers = v_from_p(sp->orig, ray->orig);
	coeffs[0] = 1;
	coeffs[1] = 2 * v_dot_product(centers, ray->dir);
	coeffs[2] = v_dot_product(centers, centers) - sp->rsq;
	det = pow(coeffs[1], 2) - 4 * coeffs[0] * coeffs[2];
	if (det < 0)
		return (min_t);
	ret_val = return_min_positive(
		(- coeffs[1] + sqrt(det)) / (2 * coeffs[0]),
		(- coeffs[1] - sqrt(det)) / (2 * coeffs[0]), min_t);
	free(centers);
	return (ret_val);
}

t_intersect		*init_objects(t_object *object, double res, t_ray *ray)
{
	t_intersect	*ans;

	if (!object || res == MAX)
		return NULL;
	if (!(ans = (t_intersect *)malloc(sizeof(t_intersect))))
		error_throw(-1);
	if (object->type == OBJ_SPHERE)
	{
		ans->color = object->color;
		ans->p_inter = p_from_v(ray->dir, res);
		ans->to_cam = v_by_scalar(ray->dir, -1);
		ans->normal = v_from_p(((t_sphere *)object->content)->orig, ans->p_inter);
		v_normalize(ans->normal);
	}
	else if (object->type == OBJ_PLANE)
	{
		ans->color = object->color;
		ans->p_inter = p_from_v(ray->dir, res);
		ans->to_cam = v_by_scalar(ray->dir, -1);
		ans->normal = v_cpy(((t_plane *)object->content)->normal);
		v_normalize(ans->normal);
		v_normalize(ans->to_cam);
	}
	else
		ans = NULL;
	return (ans);
}

double			plane_intersection(t_plane *plane, double min_t, t_ray *ray)
{
	t_vector	*tmp;
	double		coeffs[2];
	double		res;

	tmp = v_from_p(ray->orig, plane->orig);
	// v_normalize(tmp);
	//printf("tmp in plane:\n");
	//print_vector(tmp);
	coeffs[0] = v_dot_product(tmp, plane->normal);
	free(tmp);
	coeffs[1] = v_dot_product(ray->dir, plane->normal);
	if (!coeffs[1])
		coeffs[1] = 0.0001;
	res = coeffs[0] / coeffs[1];
	if (res < min_t)
		return (res);
	return (min_t);
}
t_intersect		*ray_objects_intersection(t_object *objs, t_ray *ray)
{
	t_object	*tmp;
	double		res;
	double		min_t;
	t_object	*ans;
	static int c;

	min_t = MAX;
	tmp = objs;
	ans = NULL;
	res = min_t;
	while (tmp)
	{
		if (tmp->type == OBJ_SPHERE)
		{
			// printf("defined it's a sphere\n");
			res = sphere_intersection(ray, (t_sphere *)tmp->content, min_t);
		}
		else if (tmp->type == OBJ_PLANE)
			res = plane_intersection((t_plane *)tmp->content, min_t, ray);
		else
			printf("noooo way ;( \n");
		if (res < min_t && res > 0.000001)
		{
			min_t = res;
			ans = tmp;
		}
		tmp = tmp->next;
	}
	return (init_objects(ans, min_t, ray));
}

