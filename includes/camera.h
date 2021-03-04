/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 15:10:12 by alex              #+#    #+#             */
/*   Updated: 2021/03/03 13:23:05 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H
# include "minirt.h"

typedef struct		s_camera
{
	struct s_camera	*next;
	struct s_camera	*prev;
	t_vector		dir;
	t_vector		orig;
	double			fov;
	int				id;
}					t_camera;


#endif