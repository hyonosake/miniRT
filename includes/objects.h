/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 19:53:25 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/22 11:24:11 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "minirt.h"

typedef struct			s_object
{
	struct s_object		*next;
	t_vector			color;
	void				*content;
	char				type;
}						t_object;

typedef struct			s_sphere
{
	t_vector			orig;
	t_vector			saved_orig;
	float				r;
	float				rsq;
}						t_sphere;

typedef struct			s_plane
{
	t_vector			orig;
	t_vector			saved_orig;
	t_vector			normal;
}						t_plane;

typedef struct			s_square
{
	t_vector			orig;
	t_vector			saved_orig;
	t_vector			normal;
	t_basis				b_sq;
	float				a;
	float				ahalf;
}						t_square;

typedef struct			s_trian
{
	t_vector			p[3];
	t_vector			normal;
	t_vector			exc[2];
	t_vector			saved_p[3];
	float				coords[3];
}						t_trian;

typedef struct			s_intersect
{
	t_object			hit_obj;
	t_vector			normal;
	t_vector			p_inter;
	t_vector			to_cam;
	t_vector			color;
	float				res;
	unsigned int		int_col;
	char				type;
}						t_intersect;

typedef struct			s_disk
{
	t_vector			orig;
	t_vector			saved_orig;
	t_vector			normal;
	float				radius;
}						t_disk;

typedef struct			s_cylinder
{
	t_vector			orig;
	t_vector			saved_orig;
	t_vector			axis;
	t_vector			norm;
	float				t[2];
	float				r;
	float				rsq;
	float				len;
	float				lhalf;
}						t_cylinder;

typedef struct			s_camera
{
	struct s_camera		*next;
	struct s_camera		*prev;
	t_vector			dir;
	void				*mlx_image;
	t_vector			orig;
	t_vector			saved_orig;
	float				fov;
	int					id;
}						t_camera;
#endif
