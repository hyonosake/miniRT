/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 15:10:12 by alex              #+#    #+#             */
/*   Updated: 2021/02/12 16:21:08 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H
# include "minirt.h"

typedef struct		s_camera
{
	t_vector		*dir;
	t_point			*orig;
	double			fov;
	struct s_camera	*next;
}					t_camera;


#endif