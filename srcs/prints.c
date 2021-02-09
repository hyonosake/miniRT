/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 01:14:28 by ffarah            #+#    #+#             */
/*   Updated: 2021/02/09 18:12:59 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	print_canvas(t_scene *scene)
{
	if (!scene->canvas)
		write(1, "No scene found\n", 16);
	else
	{
		printf("--------------- SCENE ----------------\n");
		printf("width: %d\n", scene->canvas->width);
		printf("height: %d\n", scene->canvas->height);
		printf("ratio: %f\n", scene->canvas->ratio);
		printf("--------------------------------------\n");
	}
}

void	print_vector(t_vector *v)
{
	if (!v)
	{
		printf("null\n");
		return ;
	}
	printf("vector:\t[%.3f %.3f %.3f]\tmod = %.3f\n", v->xv, v->yv, v->zv, v->mod);
}

void	print_point(t_point *v)
{
	if (!v)
	{
		printf("null\n");
		return ;
	}
	printf("point:\t[%.3f %.3f %.3f]\n", v->xp, v->yp, v->zp);
}

void	print_color(t_color *color)
{
	printf("RGB\t[%d %d %d]\n", color->r, color->g, color->b);
}

void	print_ray(t_ray *v)
{
	if (!v)
	{
		printf("null\n");
		return ;
	}
	print_point(v->orig);
	print_vector(v->dir);
}

void	print_cameras(t_scene *scene)
{
	t_camera	*tmp;
	int i = 0;
	if (!scene->cameras)
	{
		write(1, "No cams found\n", 16);
		return ;
	}
	tmp = scene->cameras;
	while (tmp)
	{
		printf("\n------------ CAM No %d --------------\n", ++i);
		print_vector(tmp->dir);
		print_point(tmp->orig);
		printf("fov:\t%.3f rad\n", tmp->fov);
		printf("--------------------------------------\n");
		tmp = tmp->next;
	}
}

void	print_amb_light(t_scene *scene)
{
	t_light *tmp;
	tmp = scene->ambient;
	if (!tmp)
	{
		write(1, "No ambient lights\n", 25);
		return ;
	}
	while (tmp)
	{
		printf("\n-------------- AMBIENT ---------------\n");
		print_color(tmp->color);
		printf("intens\t%.3f\n", tmp->intensity);
		printf("--------------------------------------\n");
		tmp = tmp->next;
	}
	
}


void	print_lights(t_scene *scene)
{
	t_light	*tmp;
	int i = 0;
	if (!scene->lights)
	{
		write(1, "No lights found\n", 17);
		return ;
	}
	tmp = scene->lights;
	while (tmp)
	{
		printf("\n-------------- LIGHT No %d ------------\n", ++i);
		print_point(tmp->orig);
		print_color(tmp->color);
		printf("intens\t%.3f\n", tmp->intensity);
		printf("--------------------------------------\n");
		tmp = tmp->next;
	}
}

void	print_objects(t_scene *scene)
{
	t_object *tmp;
	int i = 0;
	tmp = scene->objects;
	if (!tmp)
	{
		write(1, "No objects found\n", 18);
		return ;
	}
	while (tmp)
	{
		printf("\n-------------- OBJ No %d --------------\n", ++i);
		if (tmp->type == OBJ_SPHERE)
		{
			t_sphere *heh;
			heh = (t_sphere *)tmp->content;
			printf("\t   --- A SPHERE ---\n");
			print_point(heh->orig);
			printf("r = \t%.3f\n", heh->r);
		}
		if (tmp->type == OBJ_PLANE)
		{
			t_plane *heh;
			heh = (t_plane *)tmp->content;
			printf("\t   --- A PLANE ---\n");
			print_point(heh->orig);
			print_vector(heh->normal);
		}
		
		print_color(tmp->color);
		printf("--------------------------------------\n");
		tmp = tmp->next;
	}
}


void	print_scene(t_scene *scene)
{
	print_canvas(scene);
	print_amb_light(scene);
	print_lights(scene);
	print_objects(scene);
}
