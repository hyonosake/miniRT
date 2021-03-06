/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:23:49 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/06 20:59:29 by ffarah           ###   ########.fr       */
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
# define INSIDE_OBJ -1
# define MAGIC 1
# define VECTORIZE_COLOR 0.00392
# define OBJ_PLANE 2
# define OBJ_SQUARE 3
# define OBJ_TRIAN 4
# define OBJ_CYL 5
# define AMBIENT 1
# define DIRECT 2
# define POINTING 3
# define K_LAMB 0.93
# define K_SPEC 0.9
# define K_METAL 0.2
# define SIGMA 30
# define KEY_TAB 48
# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# include "../mlx/mlx.h"
# include "get_next_line.h"
# include "vectors.h"
# include "camera.h"
# include "ray_basis.h"
# include "matrix.h"
# include "objects.h"
# include "scene.h"
# include "intersection.h"
# include "free.h"
# include "add_scene.h"
# include "parser.h"
# include "ray_tracer.h"
# include "prints.h"

int				main(int ac, char **av);
void			error_throw(int a);
#endif