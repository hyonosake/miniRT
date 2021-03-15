/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 20:56:34 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/15 21:03:57 by ffarah           ###   ########.fr       */
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
	//printf("looking for less than %.2f\n", min_t);
	while (tmp)
	{
		if (tmp->type == OBJ_SPHERE)
			res = sphere_intersection((t_sphere *)tmp->content, ray, min_t);
		else if (tmp->type == OBJ_PLANE)
			res = plane_intersection((t_plane *)tmp->content, min_t, ray);
		else if (tmp->type == OBJ_SQUARE)
			res = square_intersection((t_square *)tmp->content, ray, min_t);
		else if (tmp->type == OBJ_TRIAN)
			res = triangle_inter((t_trian *)tmp->content, ray, min_t);
		else if (tmp->type == OBJ_CYL)
			res = cylinder_intersection((t_cylinder *)tmp->content, ray, min_t);
		else if (tmp->type == OBJ_DISK)
			res = disk_intersection((t_disk *)tmp->content, ray, min_t);
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


//void				light_complex_init(t_intersect *ans, t_scene *scene, t_light_complex *lmod)
//{

//}

//void				light_construction(t_light_complex *lmod, t_light *l, t_intersect *ans)
//{

//}

//void				specular_highlight(t_light_complex *lmod, t_intersect *ans)
//{

//}

int					blinn_phong(t_intersect *ans, t_scene *scene)
{
	t_light_complex lmod;
	t_light			*tmp;
	t_ray			s_ray;

	if (!ans)
		return (BACKGROUND_COLOR);
	//printf("???\n");
	tmp = scene->lights;
	//print_vector(&ans->color)
	lmod.total_color = color_multiply(&ans->color, &scene->ambient.color,
										scene->ambient.intensity);
	while(tmp)
	{
		if (tmp->type == DIRECT)
			lmod.to_light = point_from_vector(&tmp->orig, -1);
		else
			lmod.to_light = v_sub(&ans->p_inter, &tmp->orig);
	
		lmod.k_fading = lmod.to_light.mod;
		v_normalize(&lmod.to_light);
		s_ray = new_ray(&lmod.to_light, &ans->p_inter);
		if (!shadows(scene->objects, &s_ray, lmod.k_fading) ||
			v_dot_product(&ans->to_cam, &ans->normal) < 0)
		{
			lmod.k_diff = v_dot_product(&lmod.to_light, &ans->normal);
			if (lmod.k_diff < 0)
				lmod.k_diff = 0;
			lmod.diffuse = color_multiply(&ans->color, &tmp->color, lmod.k_diff * tmp->intensity);
			lmod.total_color = v_add(&lmod.total_color, &lmod.diffuse);
			//print_vector(&lmod.total_color, "col:");
		}
		else ;
		tmp = tmp->next;
	}
	return (col_to_int(&lmod.total_color, 1));
}

int			col_to_int(t_vector *coeffs, float to_cam)
{
	int		rgb[3];
	int		i;

	i = 0;
	rgb[0] = coeffs->xv * 255 * to_cam;
	rgb[1] = coeffs->yv * 255 * to_cam;
	rgb[2] = coeffs->zv * 255 * to_cam;
	while (i < 3)
	{
		if (rgb[i] > 255)
			rgb[i] = 255;
		++i;
	}
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}
