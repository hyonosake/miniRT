/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 20:29:54 by alex              #+#    #+#             */
/*   Updated: 2021/03/15 19:57:44 by ffarah           ###   ########.fr       */
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
	float			ratio;
}					t_canvas;

typedef struct		s_light
{
	t_vector		orig;
	t_vector		saved_orig;
	t_vector		color;
	struct s_light	*next;
	float			intensity;
	char			type;
}					t_light;

typedef struct		s_mlx
{
	char			*addr;		
	void			*init;
	void			*image;
	void			*window;
	int				lsize;
	int				bpp;
	int				endian;
	
}					t_mlx;

typedef struct		s_scene
{
	t_mlx			mlx;
	t_camera		*cameras;
	t_canvas		canvas;
	t_object		*objects;
	t_basis			r_basis;
	t_light			*lights;
	t_light			ambient;
}					t_scene;

t_scene				*define_scene(void);
void				transform_objects(t_vector *orig, t_object *objs);
void				transform_scene(t_scene *scene);
void				transform_lights(t_scene *scene);
void				add_canvas(t_scene *scene, t_canvas *new);
void				add_camera(t_scene *scene, t_camera *cam);
void				add_amb_light(t_scene *scene, t_light *amb);
void				add_light(t_scene *scene, t_light *l);
void				add_object(t_scene *scene, t_object *obj);
#endif