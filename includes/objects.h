/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 19:53:25 by ffarah            #+#    #+#             */
/*   Updated: 2021/02/27 01:08:19 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H
# include "minirt.h"
typedef struct			s_object
{
	struct	s_object	*next;
	t_color				*color;
	void				*content;
	char				type;
}						t_object;

typedef struct			s_sphere
{
	t_vector			*orig;
	double				r;
	double				rsq;
}						t_sphere;

typedef struct			s_plane
{
	t_vector			*orig;
	t_vector			*normal;
}						t_plane;

typedef struct			s_square
{
	t_vector			*orig;
	t_vector			*normal;
	double				a;
	double				asq;
}						t_square;


typedef struct			s_intersect
{
	t_vector			*normal;
	t_vector			*p_inter;
	t_vector			*to_cam;
	t_color				*color;
	double				res;
	char				type;
}						t_intersect;

#endif