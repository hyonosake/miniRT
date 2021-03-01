/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 20:56:34 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/01 16:56:13 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minirt.h"



int				shadows(t_object *objs, t_ray *ray, double min_t)
{
	t_object	*tmp;
	//t_vector	n_trans;
	//static t_object	intersected;
	double		res;

	v_normalize(ray->dir);
	// if (!intersected)
	// 	tmp = &intersected;
	// else
		tmp = objs;
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
			// intersected = tmp;
			// intersected->next = NULL;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}



int					blinn_phong(t_intersect *ans, t_scene *scene)
{
	//t_vector		*bisect;
	int				shadow;
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
		//print_vector(ans->p_inter, "p_inter:");
		t_vector	*to_light = v_add(ans->p_inter, tmp->orig);
		
		shadow_ray = new_ray(v_add(to_light, scene->cameras->orig), copy_vector(ans->p_inter));
		//print_vector(shadow_ray->dir, "shad ray:");
		shadow = shadows(scene->objects, shadow_ray, shadow_ray->dir->mod);
		if (shadow)
		{
			//printf("r_dir\t");
			//print_vector(shadow_ray->dir);
			//printf("r orig\t");
			//print_vector(shadow_ray->orig);
			//printf("found inter in\t");
			//print_vector(shadow->p_inter);
			//printf("to_l:\t");
			//print_vector(to_light);
			//printf("p_inter:\t");
			//print_vector(shadow->p_inter);
			//printf("SHADOW!\n");
			tmp = tmp->next;
			continue ;
		}
		diffuse = v_dot_product(ans->normal, shadow_ray->dir);
		if (diffuse < 0)
			diffuse = 0;
		//specular = v_dot_product(ans->normal, bisect);
		if (specular < 0)
			specular = 0;
		intens[0] += tmp->color->r / 255 * pow(diffuse,2) * tmp->intensity;
		intens[1] += tmp->color->g / 255 * pow(diffuse,2) * tmp->intensity;
		intens[2] += tmp->color->b / 255 * pow(diffuse,2) * tmp->intensity;
		tmp = tmp->next;
	}
	free_ray(shadow_ray);
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
