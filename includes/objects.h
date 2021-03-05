/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 19:53:25 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/06 01:51:59 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H
# include "minirt.h"
typedef struct			s_object
{
	struct	s_object	*next;
	t_vector			color;
	void				*content;
	char				type;
}						t_object;

typedef struct			s_sphere
{
	t_vector			orig;
	float				r;
	float				rsq;
}						t_sphere;

typedef struct			s_plane
{
	t_vector			orig;
	t_vector			normal;
}						t_plane;

typedef struct			s_square
{
	t_vector			orig;
	t_vector			normal;
	float				a;
	float				asq;
}						t_square;

typedef struct			s_trian
{
	t_vector			p[3];
	t_vector			normal;
	t_vector			magic_nums;
}						t_trian;

typedef struct			s_intersect
{
	t_vector			normal;
	t_vector			p_inter;
	t_vector			to_cam;
	t_vector			color;
	float				res;
	char				type;
}						t_intersect;

typedef struct			s_cylinder
{
	t_vector			dir;
	t_vector			orig;
	float				r;
	float				rsq;
	float				len;
}						t_cylinder;


#endif