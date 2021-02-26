/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tranform_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 15:58:59 by alex              #+#    #+#             */
/*   Updated: 2021/02/26 16:08:35 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void			transform_scene(t_scene *scene, t_camera *current_cam)
{
	t_basis		*c_matrix;
	t_point		p_current;
	t_vector	d_current;
	
	p_current = *(t_point *)v_cpy((t_vector *)current_cam->orig);
	d_current = *v_from_values(current_cam->dir->xv, current_cam->dir->yv, current_cam->dir->zv);
	c_matrix = find_transp_matrix(&d_current);
	transform_objects(scene, c_matrix, &p_current);
	transform_lights(scene->lights, c_matrix, &p_current);
	transform_current_cam(&p_current, c_matrix, scene->cameras);
	
}

void			transform_objects(t_scene *scene, t_basis *c_matrix, t_point *c_orig)
{
	t_object	*tmp;


	tmp = scene->objects;
	while(tmp)
	{
		if (tmp->type == OBJ_SPHERE)
			transform_sphere((t_sphere *)tmp->content, c_matrix, c_orig);
		else if (tmp->type == OBJ_PLANE || tmp->type == OBJ_SQUARE)
			transform_plane((t_plane *)tmp->content, c_matrix, c_orig);
		else
			printf("nooo waaaay\n");
		tmp = tmp->next;
	}
}

void			transform_sphere(t_sphere *sphere, t_basis *c_matrix, t_point *c_orig)
{
	sphere->orig = point_from_transform(c_orig, sphere->orig, c_matrix);
	//sphere->orig = (t_point *)vector_from_transform(c_matrix, (t_vector *)sphere->orig);
}

void			transform_plane(t_plane *plane,  t_basis *c_matrix, t_point *c_orig)
{
	plane->normal = vector_from_transform(c_matrix, plane->normal);
	plane->orig = point_from_transform(c_orig, plane->orig, c_matrix);
	//plane->orig = (t_point *)vector_from_transform(c_matrix, (t_vector *)plane->orig);
}

void			transform_current_cam(t_point *p_current, t_basis *c_matrix, t_camera *cams)
{
	t_camera		*tmp;
	tmp = cams;
	while(tmp)
	{
		//printf("1\n");
		tmp->orig = point_from_transform(p_current, tmp->orig, c_matrix);
		tmp->dir = vector_from_transform(c_matrix, tmp->dir);
		print_vector(tmp->dir);
		tmp = tmp->next;
	}
}

void			transform_lights(t_light *lights, t_basis *c_matrix, t_point *c_orig)
{
	t_light		*tmp;

	tmp = lights;
	while(tmp)
	{
		tmp->orig = point_from_transform(c_orig, tmp->orig, c_matrix);
		tmp = tmp->next;
	}
}

