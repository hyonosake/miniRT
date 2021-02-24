/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 20:56:34 by ffarah            #+#    #+#             */
/*   Updated: 2021/02/24 12:48:38 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minirt.h"

int					blinn_phong(t_intersect *ans, t_scene *scene)
{
	t_vector		*to_light;
	//t_vector		*bisect;
	t_intersect		*shadow;
	t_light			*tmp;
	t_ray			*shadow_ray;
	double			intens[3];
	double			diffuse;
	double			specular;

	if (ans == NULL)
		return (BACKGROUND_COLOR);
	tmp = scene->lights;
	intens[0] = scene->ambient->color->r/255 * scene->ambient->intensity;
	intens[1] = scene->ambient->color->g/255 * scene->ambient->intensity;
	intens[2] = scene->ambient->color->b/255 * scene->ambient->intensity;
	while (tmp)
	{
		to_light = v_from_p(ans->p_inter, tmp->orig);
		shadow_ray = new_ray(v_cpy(to_light), ans->p_inter);
		v_normalize(shadow_ray->dir);
		shadow = ray_objects_intersection(scene->objects, shadow_ray);
		if (shadow && shadow->res < to_light->mod)
		{
			//printf("to_l:\t");
			//print_vector(to_light);
			//printf("p_inter:\t");
			//print_point(shadow->p_inter);
			//printf("SHADOW!\n");
			tmp = tmp->next;
			continue ;
		}
		v_normalize(to_light);
		diffuse = v_dot_product(ans->normal, to_light);
		if (diffuse < 0)
			diffuse = 0;
		//specular = v_dot_product(ans->normal, bisect);
		if (specular < 0)
			specular = 0;
		intens[0] += tmp->color->r/255 * pow(diffuse,2) * tmp->intensity;
		intens[1] += tmp->color->g/255 * pow(diffuse,2) * tmp->intensity;
		intens[2] += tmp->color->b/255 * pow(diffuse,2) * tmp->intensity;
		tmp = tmp->next;
	}
	return (col_to_int(ans->color, intens));
}

int 				col_to_int(t_color *color, double *intens)
{
	int				r[3];
	int				i;
	int				res;
	i = 0;
	r[0] = color->r * intens[0];
	r[1] = color->g * intens[1];
	r[2] = color->b * intens[2];
	while (i < 2)
	{
		if (r[i] > 255)
			r[i] = 255;
		i++;
	}
	res = r[0] << 16 | r[1] << 8 | r[2];
	return (res);
}
