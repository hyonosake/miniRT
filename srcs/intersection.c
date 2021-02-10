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
	//double	res[2];
	double	coeffs[3];
	double	det;
	double	ret_val;
	t_vector *centers;
	
	centers = v_from_p(ray->orig, sp->orig);
	coeffs[0] = v_dot_product(ray->dir, ray->dir);
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
		ans->normal = v_from_p(ans->p_inter, ((t_sphere *)object->content)->orig);
		v_normalize(ans->normal);
	}
	if (object->type == OBJ_PLANE)
	{
		print_vector(((t_plane *)object)->normal);
		printf("ok?\n");
		ans->color = object->color;
		ans->p_inter = p_from_v(ray->dir, res);
		ans->to_cam = v_by_scalar(ray->dir, -1);
		ans->normal = v_cpy(((t_plane *)object)->normal);
		print_vector(ans->normal);
		v_normalize(ans->normal);
	}
	return (ans);
}

double			plane_intersection(t_plane *plane, double min_t, t_ray *ray)
{
	t_vector	*tmp;
	double		coeffs[2];
	double		res;

	//printf("1\n");
	//print_point(plane->orig);
	//print_point(ray->orig);
	tmp = v_from_p(plane->orig, ray->orig);			//sega_here
	//printf("2\n");
	v_normalize(tmp);
	//printf("3\n");
	coeffs[0] = v_dot_product(tmp, plane->normal);
	//printf("4\n");
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

	min_t = MAX;
	tmp = objs;
	ans = NULL;
	while (tmp)
	{
		if (tmp->type == OBJ_SPHERE)
		{
			if ((res = sphere_intersection(ray, (t_sphere *)tmp->content, min_t)) < min_t)
			{
				min_t = res;
				ans = tmp;
			}
		}
		else if (tmp->type == OBJ_PLANE)
		{
			print_point(((t_plane *)tmp->content)->orig);
			if ((res = plane_intersection((t_plane *)tmp->content, min_t, ray)) < min_t)
			{
				
				//printf("inside=(\n");
				min_t = res;
				ans = tmp;
			}
		}
		else
			printf("noooo way ;( \n");
		tmp = tmp->next;
	}
	return (init_objects(ans, min_t, ray));
}

