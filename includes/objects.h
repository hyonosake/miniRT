/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 19:53:25 by ffarah            #+#    #+#             */
/*   Updated: 2021/02/08 19:21:13 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H
# include "minirt.h"
typedef struct			s_object
{
	int					type;
	void				*content;
	t_ray				*intersect;
	t_color				*color;
	struct	s_object	*next;
}						t_object;

typedef struct			s_sphere
{
	t_point				*orig;
	double				r;
	double				rsq;
}						t_sphere;

typedef struct			s_plane
{
	t_point				*orig;
	t_vector			*v1;
	t_vector			*v2;
}						t_plane;

typedef struct			s_square
{
	t_point				*orig;
	t_vector			*v1;
	t_vector			*v2;
	double				a;
}						t_square;

typedef struct			s_trace
{
	double				solution;
	t_point				*p_intersect;
	t_vector			*normal;
	t_vector			*view;
	t_object			*obj;
	t_vector			*bisect;
	t_color				*col;
}						t_trace;


#endif