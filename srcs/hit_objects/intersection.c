/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 11:56:01 by alex              #+#    #+#             */
/*   Updated: 2021/03/11 23:15:05 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_intersect		*init_objects(t_object *object, float res, t_ray *ray)
{
	t_intersect	*ans;
	//t_vector		tmp;
	if (!object || res == MAX)
		return NULL;
	if (object->type == OBJ_SPHERE || object->type == INSIDE_OBJ)
		ans = init_sphere(object, res, ray);
	else if (object->type == OBJ_PLANE)
		ans = init_plane((t_plane *)object->content, res, ray, &object->color);
	else if (object->type == OBJ_SQUARE)
		ans = init_plane((t_plane *)object->content, res, ray, &object->color);
	else if (object->type == OBJ_TRIAN)
		ans = init_trian((t_trian *)object->content, res, ray, &object->color);
	else if (object->type == OBJ_CYL)
		ans = init_cylinder(object, res, ray);
	else
		ans = NULL;
	//if (ans)
	//{
	//	tmp = *ans->p_inter;
	//	free(ans->p_inter);
	//	ans->p_inter = (t_vector *)v_add((t_vector *)ray->orig, (t_vector *)&tmp);
	//}
	return (ans);
}

t_intersect		*ray_objects_intersection(t_object *objs, t_ray *ray)
{
	t_object	*tmp;
	t_object	*ans;
	float		res;
	float		min_t;

	min_t = MAX;
	tmp = objs;
	ans = NULL;
	res = min_t;
	tmp = objs;
	while (tmp)
	{
		if (tmp->type == OBJ_SPHERE)
			res = sphere_intersection(ray, tmp, min_t);
		else if (tmp->type == OBJ_PLANE)
			res = plane_intersection((t_plane *)tmp->content, min_t, ray);
		else if (tmp->type == OBJ_SQUARE)
			res = square_intersection((t_square *)tmp->content, ray, min_t);
		else if (tmp->type == OBJ_TRIAN)
			res = triangle_inter((t_trian *)tmp->content, ray, min_t);
		else if (tmp->type == OBJ_CYL)
			res = cylinder_intersection((t_cylinder *)tmp->content, ray, min_t);	
		else
			printf("parser ray_obj failed\ttype = %d\n", tmp->type);
		if (res < min_t && res > MIN)
		{
			min_t = res;
			ans = tmp;
		}
		tmp = tmp->next;
	}
	return (init_objects(ans, min_t, ray));
}
