/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 20:56:34 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/04 08:34:34 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minirt.h"



int					shadows(t_object *objs, t_ray *ray, double min_t)
{
	t_object		*tmp;
	static t_object	*prev;
	double		res;

	v_normalize(&ray->dir);
	tmp = objs;
	if (!prev)
		prev = tmp;
	while (tmp)
	{
		if (tmp->type == OBJ_SPHERE)
			res = sphere_intersection(ray, tmp, min_t);
		else if (tmp->type == OBJ_PLANE)
			res = plane_intersection((t_plane *)tmp->content, min_t, ray);
		else if (tmp->type == OBJ_SQUARE)
			res = square_intersection((t_square *)tmp->content, min_t, ray);
		else
			printf("noooo way ;(\n");	
		if (res < min_t && res > MIN)
		{
			prev = tmp;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}


t_vector			color_multiply(t_vector *v1, t_vector *v2)
{
	t_vector		new;
	
	new.xv = v1->xv * v2->xv;
	new.yv = v1->yv * v2->yv;
	new.zv = v1->zv * v2->zv;
	new.mod = 0;
	return (new);
}

double				return_max_positive(double c)
{
	if (c < 0)
		return (0);
	else if (c > 1.0)
		return (1.0);
	else
		return (c);
}

int					blinn_phong(t_intersect *ans, t_scene *scene)
{
	t_vector		bisect;
	int				shadow;
	//t_intersect		*shadow;
	t_light			*tmp;
	t_vector		to_light;
	t_ray			shadow_ray;
	t_vector		result;
	t_vector		ci;
	double			diffuse;
	double			specular;

	if (ans == NULL)
		return (BACKGROUND_COLOR);
	tmp = scene->lights;
	result = color_multiply(&ans->color, &scene->ambient.color);
	v_by_scalar(&result, scene->ambient.intensity);
	//print_vector(&result, "amb:");
	bisect = v_add(&ans->to_cam, &ans->normal);
	print_vector(&ans->to_cam, "to_c:\t");
	print_vector(&ans->normal, "norm:\t");
	v_normalize(&bisect);
	while (tmp)
	{
		to_light = v_sub(&ans->p_inter, &tmp->orig);
		shadow_ray = new_ray(&to_light, &ans->p_inter);
		shadow = shadows(scene->objects, &shadow_ray, shadow_ray.dir.mod);
		// shadow = ray_objects_intersection(scene->objects, &shadow_ray);
		if (shadow)
		{
			//printf("SHADOW!\n");
			tmp = tmp->next;
			continue ;
		}
		diffuse = v_dot_product(&ans->normal, &shadow_ray.dir);
		ci = color_multiply(&ans->color,&tmp->color);
		v_by_scalar(&ci, tmp->intensity * return_max_positive(diffuse) * K_LAMB);
		result = v_add(&result, &ci);
		specular = v_dot_product(&ans->normal, &bisect);
		t_vector		si;
		t_vector		s1;
		t_vector		s2;
		s1 = ans->color;
		v_by_scalar(&s1, K_METAL);
		s2 = v_from_values((1-K_METAL),(1-K_METAL),(1-K_METAL));
		s1 = v_add(&s1, &s2);
		si = color_multiply(&s1, &tmp->color);
		v_by_scalar(&si, tmp->intensity * pow(return_max_positive(specular), SIGMA));
		result = v_add(&result, &si);
		tmp = tmp->next;
	}
	// free_ray(shadow_ray);
	return (col_to_int(&ans->color, &result));
}

int 				col_to_int(t_vector *color, t_vector *intens)
{
	int				r[3];
	int				i;
	int				res;
	i = 0;
	r[0] = color->xv * intens->xv * 255;
	r[1] = color->yv * intens->yv * 255;
	r[2] = color->zv * intens->zv * 255;
	while (i < 2)
	{
		if (r[i] > 255)
			r[i] = 255;
		i++;
	}
	res = r[0] << 16 | r[1] << 8 | r[2];
	return (res);
}
