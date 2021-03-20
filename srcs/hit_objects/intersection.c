/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 11:56:01 by alex              #+#    #+#             */
/*   Updated: 2021/03/20 02:46:07 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void			find_object_normal(t_object *obj, t_intersect *ans, t_ray *ray)
{
	if (obj->type == TRIAN)
		ans->normal = ((t_trian *)obj->content)->normal;
	else if (obj->type == DISK)
		ans->normal = ((t_disk *)obj->content)->normal;
	else if (obj->type == PLANE)
		ans->normal = ((t_plane *)obj->content)->normal;
	else if (obj->type == SQUARE)
		ans->normal = ((t_square *)obj->content)->normal;
	else if (obj->type == SPHERE)
		ans->normal = v_sub(&((t_sphere *)obj->content)->orig, &ans->p_inter);
	else if (obj->type == CYL)
		ans->normal = create_cy_normal((t_cylinder *)obj->content, ans, ray);
	v_normalize(&ans->normal);
}

t_intersect		*init_intersect_struct(t_object *object, float res, t_ray *ray)
{
	t_intersect	*ans;
	///float		magic[3];

	if (!object || res == MAX)
		return (NULL);
	if (!(ans = (t_intersect *)malloc(sizeof(t_intersect))))
		error_throw(MALLOC_ERR);
	ans->res = res;
	ans->type = object->type;
	//if (ans->type == TRIAN && MAGIC)
	//{
	//	magic[0] = ((t_trian *)object->content)->coords[0];
	//	magic[1] = ((t_trian *)object->content)->coords[1];
	//	magic[2] = ((t_trian *)object->content)->coords[2];
	//	ans->color = v_from_values(magic[0], magic[1], magic[2]);
	//}
	//else
	ans->color = object->color;
	ans->p_inter = point_from_vector(&ray->dir, res);
	//ans->p_inter = v_sub(&ray->orig, &ans->p_inter);
	ans->to_cam = point_from_vector(&ray->dir, -1);
	find_object_normal(object, ans, ray);
	return (ans);
}

float			solve_for_plane_like(t_object *object, t_object *curr_min,
									t_ray *ray, float min_t)
{
	float		res;

	res = plane_intersection(((t_plane *)object->content), min_t, ray);
	if (res < min_t)
	{
		if ((object->type == SQUARE &&
			square_intersection((t_square *)object->content, ray, res)) ||
			(object->type == DISK &&
			disk_intersection((t_disk *)object->content, ray, res)) ||
			object->type == PLANE)
		{
			curr_min = object;
			return (res);
		}
	}
	return (min_t);
}

t_intersect		*ray_objects_intersection(t_object *objs, t_ray *ray,
											float min_t)
{
	t_object	*tmp;
	t_object	*ans;
	float		res;

	tmp = objs;
	ans = NULL;
	res = min_t;
	while (tmp)
	{
		if (tmp->type == PLANE || tmp->type == SQUARE || tmp->type == DISK)
			res = solve_for_plane_like(tmp, ans, ray, min_t);
		else if (tmp->type == SPHERE)
			res = sphere_intersection(tmp->content, ray, min_t);
		else if (tmp->type == TRIAN)
			res = triangle_inter((t_trian *)tmp->content, ray, min_t);
		else if (tmp->type == CYL)
			res = cylinder_intersection((t_cylinder *)tmp->content, ray, min_t);
		if (res < min_t && res > MIN)
		{
			min_t = res;
			ans = tmp;
		}
		tmp = tmp->next;
	}
	return (init_intersect_struct(ans, min_t, ray));
}
