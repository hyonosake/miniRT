/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 20:56:34 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/24 08:52:23 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

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

int					shadow_with_each_light(t_l_comp *lmod, t_light *l,
										t_intersect *ans, t_scene *scene)
{
	t_ray			shadow_ray;

	if (l->type == DIRECT)
	{
		lmod->to_light = point_from_vector(&l->orig, -1);
		lmod->k_fading = MAX;
	}
	else
	{
		lmod->to_light = v_sub(&ans->p_inter, &l->orig);
		lmod->k_fading = lmod->to_light.mod;
		v_normalize(&lmod->to_light);
	}
	if (v_dot_product(&lmod->to_light, &ans->normal) < 0)
		return (1);
	shadow_ray = new_ray(&lmod->to_light, &ans->p_inter);
	return (shadows(scene->objects, &shadow_ray, lmod->k_fading));
}

int					blinn_phong(t_intersect *ans, t_scene *scene)
{
	t_l_comp		lmod;
	t_light			*tmp;

	if (!ans)
		return (BACKGROUND_COLOR);
	tmp = scene->lights;
	color_define(ans, &lmod, scene);
	while (tmp)
	{
		if (!(shadow_with_each_light(&lmod, tmp, ans, scene)))
		{
			calculate_multi_color(ans, &lmod, tmp);
			calc_spec_part(ans, &lmod, tmp);
		}
		tmp = tmp->next;
	}
	return (col_to_int(&lmod.total_color, 100 / ans->to_cam.mod));
}
