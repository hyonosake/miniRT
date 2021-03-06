/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 20:29:54 by alex              #+#    #+#             */
/*   Updated: 2021/03/06 21:00:24 by ffarah           ###   ########.fr       */
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

typedef struct		s_scene
{
	t_object		*objects;
	t_light			*lights;
	t_light			ambient;
	t_camera		*cameras;
	t_canvas		canvas;
	void			*mlx_init;
	void			*mlx_image;
	void			*mlx_window;
}					t_scene;

t_scene				*define_scene(void);
void				transform_objects(t_vector *orig, t_object *objs);
void				transform_scene(t_scene *scene);
void				transform_lights(t_scene *scene);
int					blinn_phong(t_intersect *ans, t_scene *scene);
int 				col_to_int(t_vector *color, t_vector *intens, float coeff);
#endif