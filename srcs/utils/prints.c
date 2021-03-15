/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 01:14:28 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/15 11:09:22 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	print_canvas(t_scene *scene)
{
	// if (!&scene->canvas)
	// 	write(1, "No scene found\n", 16);
	// else
	// {
		printf("--------------- SCENE ----------------\n");
		printf("width: %d\n", scene->canvas.width);
		printf("height: %d\n", scene->canvas.height);
		printf("ratio: %f\n", scene->canvas.ratio);
		printf("--------------------------------------\n");
	//}
}

void	print_vector(t_vector *v, char *s)
{
	if (!v)
	{
		printf("null\n");
		return ;
	}
	if (!s)
		printf("[%.3f %.3f %.3f]\tmod = %.3f\n", v->xv, v->yv, v->zv, v->mod);
	printf("%s\t[%.3f %.3f %.3f]\tmod = %.3f\n", s, v->xv, v->yv, v->zv, v->mod);
}

void	print_color(t_vector *color)
{
	printf("RGB\t[%.2f %.2f %.2f]\n", color->xv, color->yv, color->zv);
}

void	print_ray(t_ray *v)
{
	if (!v)
	{
		printf("null\n");
		return ;
	}
	print_vector(&v->orig, "orig:");
	print_vector(&v->dir, "dir:");
}

void	print_cameras(t_scene *scene)
{
	t_camera	*tmp;

	if (!scene->cameras)
	{
		write(1, "No cams found\n", 16);
		return ;
	}
	tmp = scene->cameras;
	printf("Standing on cam %d\n", tmp->id);
	printf("\n------------ CAM No %d --------------\n", tmp->id);
	print_vector(&tmp->dir, "dir:\t");
	print_vector(&tmp->orig, "orig:\t");
	print_vector(&tmp->saved_orig, "init orig:");
	printf("fov:\t%.3f rad\n", tmp->fov);
	printf("--------------------------------------\n");
	//tmp = tmp->next;
	//while (tmp != scene->cameras)
	//{
	//	printf("\n------------ CAM No %d --------------\n", tmp->id);
	//	print_vector(&tmp->dir, "dir:\t");
	//	print_vector(&tmp->orig, "orig:\t");
	//	print_vector(&tmp->saved_orig, "init orig:");
	//	printf("fov:\t%.3f rad\n", tmp->fov);
	//	printf("--------------------------------------\n");
	//	tmp = tmp->next;
	//}
}

void	print_amb_light(t_scene *scene)
{
	t_light *tmp;
	tmp = &scene->ambient;
		printf("\n-------------- AMBIENT ---------------\n");
		print_color(&tmp->color);
		printf("intens\t%.3f\n", tmp->intensity);
		printf("--------------------------------------\n");
		tmp = tmp->next;
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
		print_vector(&tmp->orig, "orig:\t");
		print_vector(&tmp->saved_orig, "init orig:");
		print_color(&tmp->color);
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
			print_vector(&heh->orig, "orig:\t");
			print_vector(&heh->saved_orig, "init orig:");
			printf("r = \t%.3f\n", heh->r);
		}
		if (tmp->type == OBJ_PLANE)
		{
			t_plane *heh;
			heh = (t_plane *)tmp->content;
			printf("\t   --- A PLANE ---\n");
			print_vector(&heh->orig, "orig:\t");
			print_vector(&heh->saved_orig, "init orig:");
			print_vector(&heh->normal, "normal:");
		}
		if (tmp->type == OBJ_SQUARE)
		{
			t_square *heh;
			heh = (t_square *)tmp->content;
			printf("\t   --- A SQUARE ---\n");
			print_vector(&heh->orig, "orig:");
			print_vector(&heh->normal, "normal:");
			printf("side:\t%.2f\n", heh->a);
		}
		if (tmp->type == OBJ_DISK)
		{
			t_disk *heh;
			heh = (t_disk *)tmp->content;
			printf("\t   --- A DISK ---\n");
			print_vector(&heh->orig, "orig:");
			print_vector(&heh->orig, "saved_orig:");
			print_vector(&heh->normal, "normal:");
			printf("r = %.2f\n", heh->radius);
		}
			if (tmp->type == OBJ_CYL)
		{
			t_cylinder *heh;
			heh = (t_cylinder *)tmp->content;
			printf("\t   --- A CYL ---\n");
			print_vector(&heh->saved_orig, "orig:");
			print_vector(&heh->orig, "saved_orig:");
			print_vector(&heh->axis, "normal:");
			printf("r = %.2f\n", heh->r);
			printf("len = %.2f\n", heh->len);
		}
		print_vector(&tmp->color,"color:");
		printf("--------------------------------------\n");
		tmp = tmp->next;
	}
}


void	print_scene(t_scene *scene)
{
	print_canvas(scene);
	print_amb_light(scene);
	print_cameras(scene);
	print_lights(scene);
	print_objects(scene);
}

void	print_basis(t_basis *b)
{
	printf("\ti\tj\tk\n");
	printf("x\t%.2f\t%.2f\t%.2f\n", b->i.xv, b->j.xv, b->k.xv);
	printf("y\t%.2f\t%.2f\t%.2f\n", b->i.yv, b->j.yv, b->k.yv);
	printf("z\t%.2f\t%.2f\t%.2f\n", b->i.zv, b->j.zv, b->k.zv);
}