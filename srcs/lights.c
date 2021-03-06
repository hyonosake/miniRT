/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 20:56:34 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/06 23:33:44 by ffarah           ###   ########.fr       */
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
		if (tmp->type == OBJ_SPHERE)
			res = sphere_intersection(ray, tmp, min_t);
		else if (tmp->type == OBJ_PLANE)
			res = plane_intersection((t_plane *)tmp->content, min_t, ray);
		else if (tmp->type == OBJ_SQUARE)
			res = square_intersection((t_square *)tmp->content, ray, min_t);
		else if (tmp->type == OBJ_TRIAN)
			res = triangle_inter((t_trian *)tmp->content, ray, min_t);
		else
			printf("parser shadows failed\ttype = %d\n", tmp->type);	
		if (res < min_t && res > MIN)
		{
			//prev = tmp;
			//printf("saved prev! - %d!\n", prev->type);
			//print_vector(&prev->color, "color:");
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

float				return_max_positive(float c)
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
	
	int				shadow;
	t_light			*tmp;
	t_vector		to_light;
	t_ray			shadow_ray;
	t_vector		result;
	t_vector		ci;
	float			diffuse;


	if (ans == NULL)
		return (BACKGROUND_COLOR);
	tmp = scene->lights;
	result = color_multiply(&ans->color, &scene->ambient.color);
	v_by_scalar(&result, scene->ambient.intensity);
	while (tmp)
	{
		//t_vector		bisect;
		//print_vector(&tmp->orig, "l orig:");
		if (tmp->type == DIRECT)
			to_light = point_from_vector(&tmp->orig, -1);
		else
			to_light = v_sub(&ans->p_inter, &tmp->orig);
		shadow_ray = new_ray(&to_light, &ans->p_inter);
		shadow = shadows(scene->objects, &shadow_ray, shadow_ray.dir.mod);
		// shadow = ray_objects_intersection(scene->objects, &shadow_ray);
		//print_vector(&ans->p_inter, "p_inter:");
		//print_vector(&ans->normal, "normal:\t");
		v_normalize(&ans->normal);
		//print_vector(&ans->to_cam, "to_cam:\t");
		//print_vector(&to_light, "to_l:\t");
		if (shadow)
		{
			printf("SHADOW!\n");
			tmp = tmp->next;
			continue ;
		}
		if (tmp->type == DIRECT)
			diffuse = v_dot_product(&to_light, &ans->normal);
		else
			diffuse = v_dot_product(&ans->normal, &shadow_ray.dir);
		if (diffuse < 0)
			diffuse = 0;
		ci = color_multiply(&ans->color,&tmp->color);
		v_by_scalar(&ci, tmp->intensity * return_max_positive(diffuse) * K_LAMB);
		result = v_add(&result, &ci);
		//specular = v_dot_product(&ans->normal, &bisect);
		//printf("spec:%.2f\n", specular);
		//t_vector		si;
		//t_vector		s1;
		//t_vector		s2;
		//s1 = ans->color;
		//v_by_scalar(&s1, K_METAL);
		//s2 = v_from_values((1-K_METAL),(1-K_METAL),(1-K_METAL));
		//v_by_scalar(&s2, K_SPEC);
		//s1 = v_add(&s1, &s2);
		////print_vector(&s1, "spscscs");
		//si = color_multiply(&s1, &tmp->color);
		////print_vector(&si, "si senior");
		//v_by_scalar(&si, tmp->intensity *
		//			pow(return_max_positive(specular), SIGMA));
		//result = v_add(&result, &si);
		tmp = tmp->next;
	}
	return (col_to_int(&ans->color, &result, ans->res));
}

int 				col_to_int(t_vector *color, t_vector *intens, float coeff)
{
	int				r[3];
	int				i;
	float			cam_dist;
	i = 0;

	// cam_dist = 50 / coeff;
	// if (cam_dist > 1)
		cam_dist = 50 / coeff;
		//printf("coeff = %.2f\n", coeff);

	cam_dist = 	1;
	r[0] = color->xv * intens->xv * 255 * cam_dist;
	r[1] = color->yv * intens->yv * 255 * cam_dist;
	r[2] = color->zv * intens->zv * 255 * cam_dist;
	while (i < 2)
	{
		if (r[i] > 255)
			r[i] = 255;
		i++;
	}
	return (r[0] << 16 | r[1] << 8 | r[2]);
}
