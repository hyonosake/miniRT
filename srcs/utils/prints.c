/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 01:14:28 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/19 15:19:47 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void			print_amb_light(t_scene *scene)
{
	t_light		*tmp;

	tmp = &scene->ambient;
	printf("\n-------------- AMBIENT ---------------\n");
	print_vector(&tmp->color, "amb_color");
	printf("intens\t%.3f\n", tmp->intensity);
	printf("--------------------------------------\n");
}

void			print_lights(t_scene *scene)
{
	t_light		*tmp;
	int			i;

	i = 0;
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
		print_vector(&tmp->color, "l color");
		printf("intens\t%.3f\n", tmp->intensity);
		printf("--------------------------------------\n");
		tmp = tmp->next;
	}
}

void			print_scene(t_scene *scene)
{
	print_canvas(scene);
	print_amb_light(scene);
	print_cameras(scene);
	print_lights(scene);
	print_objects(scene);
}

void			print_basis(t_basis *b)
{
	printf("\ti\tj\tk\n");
	printf("x\t%.2f\t%.2f\t%.2f\n", b->i.xv, b->j.xv, b->k.xv);
	printf("y\t%.2f\t%.2f\t%.2f\n", b->i.yv, b->j.yv, b->k.yv);
	printf("z\t%.2f\t%.2f\t%.2f\n", b->i.zv, b->j.zv, b->k.zv);
}

void			print_objects(t_scene *scene)
{
	t_object	*tmp;
	int			i;
	t_sphere	*heh_sp;
	t_plane		*heh_pl;
	t_square	*heh_sq;
	t_disk		*heh_d;
	t_cylinder	*heh_cy;
	i = 0;
	tmp = scene->objects;
	if (!tmp)
	{
		write(1, "No objects found\n", 18);
		return ;
	}
	while (tmp)
	{
		printf("\n-------------- OBJ No %d --------------\n", ++i);
		if (tmp->type == SPHERE)
		{
			heh_sp = (t_sphere *)tmp->content;
			printf("\t   --- A SPHERE ---\n");
			print_vector(&heh_sp->orig, "orig:\t");
			print_vector(&heh_sp->saved_orig, "init orig:");
			printf("r = \t%.3f\n", heh_sp->r);
		}
		else if (tmp->type == PLANE)
		{
			heh_pl = (t_plane *)tmp->content;
			printf("\t   --- A PLANE ---\n");
			print_vector(&heh_pl->orig, "orig:\t");
			print_vector(&heh_pl->saved_orig, "init orig:");
			print_vector(&heh_pl->normal, "normal:");
		}
		else if (tmp->type == SQUARE)
		{
			heh_sq = (t_square *)tmp->content;
			printf("\t   --- A SQUARE ---\n");
			print_vector(&heh_sq->orig, "orig:");
			print_vector(&heh_sq->normal, "normal:");
			printf("side:\t%.2f\n", heh_sq->a);
		}
		else if (tmp->type == DISK)
		{
			heh_d = (t_disk *)tmp->content;
			printf("\t   --- A DISK ---\n");
			print_vector(&heh_d->orig, "orig:");
			print_vector(&heh_d->saved_orig, "saved_orig:");
			print_vector(&heh_d->normal, "normal:");
			printf("r = %.2f\n", heh_d->radius);
		}
		else if (tmp->type == CYL)
		{
			heh_cy = (t_cylinder *)tmp->content;
			printf("\t   --- A CYL ---\n");
			print_vector(&heh_cy->saved_orig, "orig:");
			print_vector(&heh_cy->orig, "saved_orig:");
			print_vector(&heh_cy->axis, "normal:");
			printf("r = %.2f\n", heh_cy->r);
			printf("len = %.2f\n", heh_cy->len);
		}
		print_vector(&tmp->color, "color:");
		printf("--------------------------------------\n");
		tmp = tmp->next;
	}
}
