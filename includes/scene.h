/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 20:29:54 by alex              #+#    #+#             */
/*   Updated: 2021/03/01 00:23:19 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "minirt.h"
typedef struct		s_canvas
{
	int 			width;
	int 			height;
	int				x_pixel;
	int				y_pixel;
	double			ratio;
}					t_canvas;

typedef struct		s_scene
{
	t_object		*objects;
	t_light			*lights;
	t_light			*ambient;
	t_camera		*cameras;
	t_canvas		*canvas;
	void			*mlx_init;
	void			*mlx_image;
	void			*mlx_window;
}					t_scene;

t_scene		*define_scene(void);
#endif