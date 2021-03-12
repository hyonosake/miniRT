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

// void			transform_scene(t_scene *scene)
// {
// 	t_basis		*c_matrix;
// 	t_vector	p_current;
// 	t_vector	d_current;
	
// 	p_current = *copy_vector(scene->cameras->orig);
// 	d_current = *copy_vector(scene->cameras->dir);
// 	// print_vector(&p_current,"p end");
// 	// print_vector(&d_current,"d end");
// 	c_matrix = find_transp_matrix(&d_current);
// 	transform_objects(scene, c_matrix, &p_current);
// 	transform_lights(scene->lights, c_matrix, &p_current);
// 	//print_basis(c_matrix);
// 	//print_vector(scene->cameras->dir,"cam orig");
// 	//print_vector((((t_sphere *)scene->objects->content)->orig), "sph in that coords:");
// 	basis_free(c_matrix);
// }

// void			transform_objects(t_scene *scene, t_basis *c_matrix, t_vector *c_orig)
// {
// 	t_object	*tmp;


// 	tmp = scene->objects;
// 	while(tmp)
// 	{
// 		if (tmp->type == OBJ_SPHERE)
// 			transform_sphere((t_sphere *)tmp->content, c_matrix, c_orig);
// 		else if (tmp->type == OBJ_PLANE || tmp->type == OBJ_SQUARE)
// 			transform_plane((t_plane *)tmp->content, c_matrix, c_orig);
// 		else
// 			printf("nooo waaaay\n");
// 		tmp = tmp->next;
// 	}
// }

// void			transform_sphere(t_sphere *sphere, t_basis *c_matrix, t_vector *c_orig)
// {
// 	transform_point(c_orig, sphere->orig, c_matrix);
// }

// void			transform_plane(t_plane *plane,  t_basis *c_matrix, t_vector *c_orig)
// {
// 	transform_point(c_orig, plane->orig, c_matrix);
// 	transform_vector(c_matrix, plane->normal);
// }

// void			transform_cams(t_vector *current_orig, t_basis *c_matrix, t_camera *cams)
// {
// 	t_camera	*tmp;

// 	tmp = cams;
// 	transform_vector(c_matrix, tmp->dir);
// 	transform_point(current_orig, tmp->orig, c_matrix);
// 	tmp = tmp->next;
// 	while(tmp != cams)
// 	{
// 		transform_vector(c_matrix, tmp->dir);
// 		transform_point(current_orig, tmp->orig, c_matrix);
// 		tmp = tmp->next;
// 	}
// }

// void			transform_lights(t_light *lights, t_basis *c_matrix, t_vector *current_orig)
// {
// 	t_light		*tmp;

// 	tmp = lights;
// 	while(tmp)
// 	{
// 		transform_point(current_orig, tmp->orig, c_matrix);
// 		tmp = tmp->next;
// 	}
// }


void			transform_lights(t_scene *scene)
{
	t_light		*tmp;

	tmp = scene->lights;
	while(tmp)
	{
		if (tmp->type == POINTING)
		{
			print_vector(&scene->cameras->saved_orig ,"cam pos");
			print_vector(&tmp->saved_orig ,"l pos\t");
			tmp->orig = v_sub(&scene->cameras->saved_orig, &tmp->saved_orig);
			print_vector(&tmp->orig ,"l orig\t");
		}
		tmp = tmp->next;
	}
}

void			transform_objects(t_vector *orig, t_object *objs, t_vector *dir)
{
	t_object	*tmp;
	void		*c;

	tmp = objs;
	if (!tmp)
		error_throw(-3);
	while(tmp)
	{
		c = tmp->content;
		if (tmp->type == OBJ_SPHERE)
			((t_sphere *)c)->orig = v_sub(orig, &((t_sphere *)c)->saved_orig);
		else if  (tmp->type == OBJ_PLANE)
		{
			((t_plane *)c)->orig = v_sub(orig, &((t_plane *)c)->saved_orig);
			if (v_dot_product((&((t_plane *)c)->normal), dir) > 0)
				v_by_scalar((&((t_plane *)c)->normal), -1);
		}
		else if  (tmp->type == OBJ_SQUARE)
			((t_square *)c)->orig = v_sub(orig, &((t_square *)c)->saved_orig);
		else if  (tmp->type == OBJ_TRIAN)
		{
			((t_trian *)c)->p[0] = v_sub(orig, &((t_trian *)c)->saved_p[0]);
			((t_trian *)c)->p[1] = v_sub(orig, &((t_trian *)c)->saved_p[1]);
			((t_trian *)c)->p[2] = v_sub(orig, &((t_trian *)c)->saved_p[2]);
		}
		else if  (tmp->type == OBJ_CYL)
			((t_cylinder *)tmp->content)->orig =
				v_sub(orig, &((t_cylinder *)tmp->content)->saved_orig);	
		else if  (tmp->type == OBJ_DISK)
			((t_disk *)c)->orig = v_sub(orig, &((t_disk *)c)->saved_orig);
		tmp = tmp->next;			
	}
}

void	transform_cameras(t_camera *cams)
{
	t_camera	*tmp;

	tmp = cams;
	tmp->orig = v_from_values(0,0,0);
	tmp = tmp->next;
	while (tmp != cams)
	{
		tmp->orig = v_sub(&cams->saved_orig, &tmp->saved_orig);
		tmp = tmp->next;
	}
}


void			transform_scene(t_scene *scene)
{
	scene->r_basis = basis_init(&scene->cameras->dir);
	transform_lights(scene);
	transform_objects(&scene->cameras->saved_orig, scene->objects,
						&scene->cameras->dir);
	transform_cameras(scene->cameras);
}

