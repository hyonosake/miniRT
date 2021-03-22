/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 01:14:28 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/22 12:09:43 by ffarah           ###   ########.fr       */
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

void			print_basis(t_basis *b)
{
	printf("\ti\tj\tk\n");
	printf("x\t%.2f\t%.2f\t%.2f\n", b->i.xv, b->j.xv, b->k.xv);
	printf("y\t%.2f\t%.2f\t%.2f\n", b->i.yv, b->j.yv, b->k.yv);
	printf("z\t%.2f\t%.2f\t%.2f\n", b->i.zv, b->j.zv, b->k.zv);
}
