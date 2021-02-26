/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 15:10:12 by alex              #+#    #+#             */
/*   Updated: 2021/02/26 13:37:48 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H
# include "minirt.h"

typedef struct		s_camera
{
	struct s_camera	*next;
	struct s_camera	*prev;
	t_vector		*dir;
	t_point			*orig;
	double			fov;
}					t_camera;


#endif