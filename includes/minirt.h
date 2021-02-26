/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:23:49 by ffarah            #+#    #+#             */
/*   Updated: 2021/02/26 16:27:29 by ffarah           ###   ########.fr       */
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
# define MIN 0.0001
# define BACKGROUND_COLOR 0x0
# define P_LIGHT 1
# define D_LIGHT 2
# define OBJ_SPHERE 1
# define OBJ_PLANE 2
# define OBJ_SQUARE 3
# define OBJ_TRIAN 4
# define OBJ_CYL 5
# define AMBIENT 1
# define DIRECT 2
# define POINTING 3
# define ESC 52
# include "../mlx/mlx.h"
# include "get_next_line.h"
# include "vectors.h"
# include "vector_utils.h"
# include "camera.h"
# include "ray_basis.h"
# include "matrix.h"
# include "color.h"
# include "objects.h"
# include "scene.h"
# include "lights.h"
# include "intersection.h"
# include "free.h"
# include "transform.h"
# include "add_scene.h"
# include "parser.h"
# include "ray_tracer.h"
# include "prints.h"

int				main(int ac, char **av);
#endif