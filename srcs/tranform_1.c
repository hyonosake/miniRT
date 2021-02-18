/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tranform_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 15:58:59 by alex              #+#    #+#             */
/*   Updated: 2021/02/18 18:30:40 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void			transform_scene(t_scene *scene, t_camera *current_cam)
{
	t_basis		*c_matrix;
	t_point		*trans_p;
	c_matrix = find_transp_matrix(scene, current_cam);
	transform_objects(scene, c_matrix, current_cam->orig);
	transform_lights(scene->lights, c_matrix, current_cam->orig);
	transform_current_cam(current_cam, c_matrix);
}

void			transform_objects(t_scene *scene, t_basis *c_matrix, t_point *c_orig)
{
	t_object	*tmp;
	
	tmp = scene->objects;
	while(tmp)
	{
		if (tmp->type == OBJ_SPHERE)
			transform_sphere((t_sphere *)tmp->content, c_matrix, c_orig);
		else if (tmp->type == OBJ_PLANE)
			transform_plane((t_plane *)tmp->content, c_matrix, c_orig);
		else
			printf("nooo waaaay\n");
		tmp = tmp->next;
	}
}

void			transform_sphere(t_sphere *sphere, t_basis *c_matrix, t_point *c_orig)
{
	sphere->orig = point_from_transform(c_orig, sphere->orig);
	sphere->orig = (t_point *)vector_from_transform(c_matrix, (t_vector *)sphere->orig);
}

void			transform_plane(t_plane *plane,  t_basis *c_matrix, t_point *c_orig)
{
	plane->normal = vector_from_transform(c_matrix, plane->normal);
	plane->orig = point_from_transform(c_orig, plane->orig);
	plane->orig = (t_point *)vector_from_transform(c_matrix, (t_vector *)plane->orig);
}

void			transform_current_cam(t_camera *current_cam, t_basis *c_matrix)
{
	free(current_cam->orig);
	free(current_cam->dir);
	current_cam->dir = v_from_values(0,0,1);
	current_cam->orig = p_from_values(0,0,0);
		// current_cam->orig = point_from_transform(current_cam->orig, current_cam->orig);
		// current_cam->dir = vector_from_transform(c_matrix, current_cam->dir);
}

void			transform_lights(t_light *lights, t_basis *c_matrix, t_point *c_orig)
{
	t_light		*tmp;

	tmp = lights;
	while(tmp)
	{
		tmp->orig = point_from_transform(c_orig, tmp->orig);
		tmp->orig = (t_point *)vector_from_transform(c_matrix, (t_vector *)tmp->orig);
		tmp = tmp->next;
	}
}

