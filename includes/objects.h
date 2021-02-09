/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 19:53:25 by ffarah            #+#    #+#             */
/*   Updated: 2021/02/09 18:06:17 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H
# include "minirt.h"
typedef struct			s_object
{
	int					type;
	void				*content;
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
	t_vector			*normal;
}						t_plane;

typedef struct			s_square
{
	t_point				*orig;
	t_vector			*v1;
	t_vector			*v2;
	double				a;
}						t_square;


typedef struct			s_intersect
{
	t_vector			*normal;
	t_point				*p_inter;
	t_vector			*to_cam;
	t_color				*color;
}						t_intersect;


#endif