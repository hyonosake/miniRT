/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 20:56:34 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/17 11:07:56 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minirt.h"



int					shadows(t_object *objs, t_ray *ray, float min_t)
{
	t_object		*tmp;
	float			res;

	v_normalize(&ray->dir);
	tmp = objs;
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
		{
			//printf("========== shadow ===========\n");
			//print_vector(&ray->orig, "ray->orig");
			res = cylinder_intersection((t_cylinder *)tmp->content, ray, min_t);
			//printf("==============================\n");
		}
		else if (tmp->type == OBJ_DISK)
			res = disk_intersection((t_disk *)tmp->content, ray, min_t);
		else
			printf("parser shadows failed\ttype = %d\n", tmp->type);	
		if (res < min_t && res > MIN)
		{
			return (tmp->type);
		}
		tmp = tmp->next;
	}
	//printf("let there be light\n");
	//t_vector temp = point_from_vector(&ray->dir, res);
	//temp = v_sub(&ray->orig, &temp);
	//print_vector(&temp, "p_inters");
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

int				blinn_phong(t_intersect *ans, t_scene *scene)
{
	t_light_complex lmod;
	t_light			*tmp;
	t_ray			s_ray;

	if (!ans)
		return (BACKGROUND_COLOR);
	tmp = scene->lights;
	//ans->to_cam = v_sub(&ans->p_inter, &scene->cameras->orig);
	v_normalize(&ans->to_cam);
	lmod.total_color = color_multiply(&ans->color, &scene->ambient.color,
										scene->ambient.intensity);
	if (v_dot_product(&ans->to_cam, &ans->normal) < 0)
		v_by_scalar(&ans->normal, -1);
	while(tmp)
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
			lmod.k_diff = v_dot_product(&lmod.to_light, &ans->normal);
			if (lmod.k_diff < 0)
				lmod.k_diff = 0;
			lmod.diffuse = color_multiply(&ans->color, &tmp->color,
				lmod.k_diff * tmp->intensity);
			lmod.total_color = v_add(&lmod.total_color, &lmod.diffuse);
			lmod.spec = v_add(&ans->to_cam, &lmod.to_light);
			v_normalize(&lmod.spec);
			lmod.k_spec = v_dot_product(&lmod.spec, &ans->normal);
			if (lmod.k_spec < 0)
				lmod.k_spec = 0;
			lmod.k_spec = pow(lmod.k_spec, 90) * tmp->intensity;
			lmod.spec = tmp->color;
			v_by_scalar(&lmod.spec, lmod.k_spec);
			lmod.total_color = v_add(&lmod.total_color, &lmod.spec);
		}
		else ;
		//{
		//	printf("SHADOW\n%.2f\n", ans->res);
		//	print_vector(&ans->to_cam, "to_c:");
		//	print_vector(&ans->normal, "norm:");
		//	print_vector(&lmod.to_light, "to_l");
		//}
		//	printf("shadows!\n");
		tmp = tmp->next;
	}
	return (col_to_int(&lmod.total_color, 100 / ans->to_cam.mod));
}

int			col_to_int(t_vector *coeffs, float to_cam)
{
	int		rgb[3];
	int		i;

	if (to_cam > 1)
		to_cam = 1;
	else if (to_cam < 0.2)
		to_cam = 0.2;
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
