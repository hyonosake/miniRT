/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 20:29:54 by alex              #+#    #+#             */
/*   Updated: 2021/02/06 15:25:30 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "minirt.h"

typedef struct		s_canvas
{
	int 			width;
	int 			height;
	double			ratio;
}					t_canvas;

typedef struct		s_scene
{
	t_camera		*cameras;
	t_canvas		*canvas;
	//t_object		*objects;
	t_light			*lights;
	t_light			*ambient;
}					t_scene;



#endif