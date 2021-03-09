/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 20:56:34 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/09 13:16:13 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minirt.h"



int					shadows(t_object *objs, t_ray *ray, float min_t)
{
	t_object		*tmp;
	//static t_object	*prev;
	float		res;

	v_normalize(&ray->dir);
	tmp = objs;
	//if (!prev)
	//	prev = tmp;
	while (tmp)
	{
		if (tmp->type == OBJ_SPHERE || tmp->type == INSIDE_OBJ)
		{
			//printf("shadow ");
			res = sphere_intersection(ray, tmp, min_t);
		}
		else if (tmp->type == OBJ_PLANE)
			res = plane_intersection((t_plane *)tmp->content, min_t, ray);
		else if (tmp->type == OBJ_SQUARE)
			res = square_intersection((t_square *)tmp->content, ray, min_t);
		else if (tmp->type == OBJ_TRIAN)
			res = triangle_inter((t_trian *)tmp->content, ray, min_t);
		else
			printf("parser shadows failed\ttype = %d\n", tmp->type);	
		if (res < min_t && res > MIN)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}


t_vector			color_multiply(t_vector *v1, t_vector *v2, double k)
{
	t_vector		new;
	
	new.xv = v1->xv * v2->xv * k;
	new.yv = v1->yv * v2->yv * k;
	new.zv = v1->zv * v2->zv * k;
	new.mod = 0;
	return (new);
}

float				return_max_positive(float c)
{
	//printf("k = %.2f\n", c);
	if (c < 0)
		return (0);
	else if (c > 1.0)
		return (1.0);
	else
		return (c);
}

void				turn_into_magic(t_light_complex *b_phong, t_intersect *ans)
{
	float			k;
	t_vector		reference;
	
	reference = v_from_values(0,1,0);
	if (MAGIC == 1)
	{
		k = v_dot_product(&reference, &ans->normal);
		if (k > 0)
		{
			b_phong->obj_color.xv = k * 0.9;
			b_phong->obj_color.yv = (1 - k) * 0.9;
		}
		else
		{
			b_phong->obj_color.xv = (1 + k) * 0.9;
			b_phong->obj_color.yv = - k * 0.9;
		}
		b_phong->obj_color.zv = 0.3;
	}
}


void				light_complex_init(t_intersect *ans, t_scene *scene, t_light_complex *b_phong)
{
	b_phong->amb_color = scene->ambient.color;
	b_phong->k_amb = scene->ambient.intensity;
	if (MAGIC && ans->type == OBJ_SPHERE)
		turn_into_magic(b_phong, ans);
	else
		b_phong->obj_color = ans->color;
	b_phong->total_color = color_multiply(&b_phong->obj_color, &b_phong->amb_color, b_phong->k_amb);
}

void				light_construction(t_light_complex *b_phong, t_light *l, t_intersect *ans)
{
	b_phong->k_diff = return_max_positive(v_dot_product(&b_phong->to_light, &ans->normal));
	b_phong->diffuse = color_multiply(&l->color, &b_phong->obj_color,
										b_phong->k_diff * b_phong->k_light * 0.7);
	b_phong->total_color = v_add(&b_phong->total_color, &b_phong->diffuse);
	//specular_highlight(b_phong, ans);
}

void				specular_highlight(t_light_complex *b_phong, t_intersect *ans)
{
	t_vector		bisect;
	t_vector		spec[2];

	bisect = v_add(&ans->to_cam, &b_phong->to_light);
	v_normalize(&bisect);
	b_phong->k_spec = return_max_positive(v_dot_product(&bisect, &ans->normal));
	if (b_phong->k_spec < 0.8)
		return ;
	spec[0] = point_from_vector(&b_phong->obj_color, K_METAL);
	spec[1] = v_from_values((1 - K_METAL), (1 - K_METAL), (1 - K_METAL));
	spec[0] = v_add(&spec[0], &spec[1]);
	b_phong->spec = color_multiply(&b_phong->obj_color, &spec[0],
									pow(b_phong->k_spec, SIGMA) * b_phong->k_light);
	b_phong->total_color = v_add(&b_phong->total_color, &b_phong->spec);
}


int					blinn_phong(t_intersect *ans, t_scene *scene)
{
	t_light			*tmp;
	t_light_complex	b_phong;
	t_ray			shadow_ray;
	//t_vector		to_light;
	//int				shadow;
	if (ans == NULL)
		return (BACKGROUND_COLOR);
	v_normalize(&ans->normal);
	v_normalize(&ans->to_cam);
	tmp = scene->lights;
	light_complex_init(ans, scene, &b_phong);
	while (tmp)
	{
		b_phong.l_type = tmp->type;
		b_phong.k_light = tmp->intensity;
		if (tmp->type == DIRECT)
			b_phong.to_light = point_from_vector(&tmp->orig, -1);
		else
			b_phong.to_light = v_sub(&ans->p_inter, &tmp->orig);
		//to_light = v_sub(&ans->p_inter, &tmp->orig);
		//b_phong.k_fading = shadow_ray.dir.mod;
		shadow_ray = new_ray(&b_phong.to_light, &ans->p_inter);
		v_normalize(&b_phong.to_light);
		if (!shadows(scene->objects, &shadow_ray, shadow_ray.dir.mod))
			light_construction(&b_phong, tmp, ans);
		else
			printf("SHADOW!\n");
		tmp = tmp->next;
	}
	return (col_to_int(&b_phong.total_color));
}

int		col_to_int(t_vector	*coeffs)
{
	int rgb[3];
	int i;

	i = 0;
	rgb[0] = coeffs->xv * 255;
	rgb[1] = coeffs->yv * 255;
	rgb[2] = coeffs->zv * 255;
	while (i < 3)
	{
		if (rgb[i] > 255)
			rgb[i] = 255;
		i++;
	}
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}
