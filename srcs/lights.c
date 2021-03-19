/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 20:56:34 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/19 15:25:55 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int					shadows(t_object *objs, t_ray *ray, float min_t)
{
	t_object		*tmp;
	float			res;
	static t_object *shad;

	v_normalize(&ray->dir);
	tmp = objs;
	while (tmp)
	{
		if (tmp->type == PLANE || tmp->type == SQUARE || tmp->type == DISK)
			res = solve_for_plane_like(tmp, shad, ray, min_t);
		else if (tmp->type == SPHERE)
			res = sphere_intersection((t_sphere *)tmp->content, ray, min_t);
		else if (tmp->type == TRIAN)
			res = triangle_inter((t_trian *)tmp->content, ray, min_t);
		else if (tmp->type == CYL)
			res = cylinder_intersection((t_cylinder *)tmp->content, ray, min_t);
		if (res < min_t && res > MIN)
		{
			return (tmp->type);
		}
		tmp = tmp->next;
	}
	return (0);
}

void				calc_spec_part(t_intersect *ans, t_l_comp *lmod,
							t_light *l)
{
	lmod->spec = v_add(&ans->to_cam, &lmod->to_light);
	v_normalize(&lmod->spec);
	lmod->k_spec = v_dot_product(&lmod->spec, &ans->normal);
	if (lmod->k_spec < 0)
		lmod->k_spec = 0;
	lmod->k_spec = pow(lmod->k_spec, 90) * l->intensity;
	lmod->spec = l->color;
	v_by_scalar(&lmod->spec, lmod->k_spec);
	lmod->total_color = v_add(&lmod->total_color, &lmod->spec);
}

void				calculate_multi_color(t_intersect *ans, t_l_comp *lmod,
							t_light *l)
{
	lmod->k_diff = v_dot_product(&lmod->to_light, &ans->normal);
	if (lmod->k_diff < 0)
		lmod->k_diff = 0;
	lmod->diffuse = color_multiply(&ans->color, &l->color,
		lmod->k_diff * l->intensity);
	lmod->total_color = v_add(&lmod->total_color, &lmod->diffuse);
}

void				color_define(t_intersect *ans, t_l_comp *lmod,
									t_scene *scene)
{
	if (v_dot_product(&ans->to_cam, &ans->normal) < 0)
		v_by_scalar(&ans->normal, -1);
	lmod->total_color = color_multiply(&ans->color, &scene->ambient.color,
										scene->ambient.intensity);
}

int					blinn_phong(t_intersect *ans, t_scene *scene)
{
	t_l_comp		lmod;
	t_light			*tmp;
	t_ray			s_ray;

	if (!ans)
		return (BACKGROUND_COLOR);
	tmp = scene->lights;
	color_define(ans, &lmod, scene);
	while (tmp)
	{
		if (tmp->type == DIRECT)
			lmod.to_light = point_from_vector(&tmp->orig, -1);
		else
			lmod.to_light = v_sub(&ans->p_inter, &tmp->orig);
		lmod.k_fading = lmod.to_light.mod;
		v_normalize(&lmod.to_light);
		s_ray = new_ray(&lmod.to_light, &ans->p_inter);
		if (!shadows(scene->objects, &s_ray, lmod.k_fading))
		{
			calculate_multi_color(ans, &lmod, tmp);
			calc_spec_part(ans, &lmod, tmp);
		}
		tmp = tmp->next;
	}
	return (col_to_int(&lmod.total_color, 100 / ans->to_cam.mod));
}
