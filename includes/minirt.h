/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:23:49 by ffarah            #+#    #+#             */
/*   Updated: 2021/02/09 18:11:06 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include <stdio.h>
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# define MAX 1000000
# define OBJ_SPHERE 1
# define OBJ_PLANE 2
# define OBJ_SQUARE 3
# define OBJ_TRIAN 4
# define OBJ_CYL 5
# define AMBIENT 1
# define DIRECT 2
# define POINTING 3
# include "../minilibx/mlx.h"
# include "vectors.h"
# include "camera.h"
# include "color.h"
# include "get_next_line.h"
# include "vector_utils.h"
# include "ray_basis.h"
# include "lights.h"
# include "objects.h"
# include "scene.h"
# include "add_scene.h"
# include "parser.h"
# include "intersection.h"
# include "prints.h"


t_scene		*define_scene();

#endif