/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 20:33:43 by alex              #+#    #+#             */
/*   Updated: 2021/03/03 14:50:13 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_scene		*define_scene(void)
{
	t_scene *new;

	if (!(new = (t_scene *)malloc(sizeof(t_scene))))
		error_throw(-1);
	// new->canvas = NULL;
	new->cameras = NULL;
	new->objects = NULL;
	new->lights = NULL;
	// new->ambient = NULL;
	new->mlx_init = NULL;
	new->mlx_window = NULL;
	return (new);
}
