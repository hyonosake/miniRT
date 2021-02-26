///* ************************************************************************** */
///*                                                                            */
///*                                                        :::      ::::::::   */
///*   tranform_1.c                                       :+:      :+:    :+:   */
///*                                                    +:+ +:+         +:+     */
///*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
///*                                                +#+#+#+#+#+   +#+           */
///*   Created: 2021/02/16 15:58:59 by alex              #+#    #+#             */
///*   Updated: 2021/02/27 00:20:02 by ffarah           ###   ########.fr       */
///*                                                                            */
///* ************************************************************************** */

#include "../includes/minirt.h"

void			transform_scene(t_scene *scene, t_camera *current_cam)
{
	t_basis		*c_matrix;
	t_vector		p_current;
	t_vector	d_current;
	
	p_current = *copy_vector(current_cam->orig);
	d_current = *v_from_values(current_cam->dir->xv, current_cam->dir->yv, current_cam->dir->zv);
	c_matrix = find_transp_matrix(&d_current);
	transform_objects(scene, c_matrix, &p_current);
	transform_lights(scene->lights, c_matrix, &p_current);
	transform_cams(&p_current, c_matrix, current_cam);
	print_scene(scene);
}

void			transform_objects(t_scene *scene, t_basis *c_matrix, t_vector *c_orig)
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

void			transform_sphere(t_sphere *sphere, t_basis *c_matrix, t_vector *c_orig)
{
	transform_point(c_orig, sphere->orig, c_matrix);
}

void			transform_plane(t_plane *plane,  t_basis *c_matrix, t_vector *c_orig)
{
	transform_vector(c_matrix, plane->normal);
	transform_point(c_orig, plane->orig, c_matrix);
}

void			transform_cams(t_vector *current_orig, t_basis *c_matrix, t_camera *cams)
{
	t_camera	*tmp;
	t_camera	*first;
	tmp = cams;
	transform_vector(c_matrix, tmp->orig);
	transform_point(current_orig, tmp->orig, c_matrix);
	first = tmp;
	tmp = tmp->next;
	while(tmp != first)
	{
		//printf("1\n");
		transform_vector(c_matrix, tmp->orig);
		transform_point(current_orig, tmp->orig, c_matrix);
		//print_vector(tmp->dir);
		tmp = tmp->next;
	}
}

void			transform_lights(t_light *lights, t_basis *c_matrix, t_vector *current_orig)
{
	t_light		*tmp;

	tmp = lights;
	while(tmp)
	{
		transform_point(current_orig, tmp->orig, c_matrix);
		tmp = tmp->next;
	}
}

