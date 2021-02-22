/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 11:56:01 by alex              #+#    #+#             */
/*   Updated: 2021/02/22 20:13:49 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_intersect		*init_objects(t_object *object, double res, t_ray *ray)
{
	t_intersect	*ans;
	if (!object || res == MAX)
		return NULL;
	if (object->type == OBJ_SPHERE)
		ans = init_sphere((t_sphere *)object->content, res, ray, object->color);
	else if (object->type == OBJ_PLANE)
	{
		ans = init_plane((t_plane *)object->content, res, ray, object->color);
		//printf("res in pl = %.3f\n", res);
	}
	else if (object->type == OBJ_SQUARE)
	{
		ans = init_plane((t_plane *)object->content, res, ray, object->color);
		//printf("res in sq = %.3f\n", res);
	}
	else
		ans = NULL;
	return (ans);
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
	res = min_t;
	while (tmp)
	{
		if (tmp->type == OBJ_SPHERE)
			res = sphere_intersection(ray, (t_sphere *)tmp->content, min_t);
		else if (tmp->type == OBJ_PLANE)
			res = plane_intersection((t_plane *)tmp->content, min_t, ray);
		else if (tmp->type == OBJ_SQUARE)
			res = square_intersection((t_square *)tmp->content, min_t, ray);
		else
			printf("noooo way ;( \n");
		if (res < min_t && res > 0.001)
		{
			min_t = res;
			ans = tmp;
		}
		tmp = tmp->next;
	}
	return (init_objects(ans, min_t, ray));
}
