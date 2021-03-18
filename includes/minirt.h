/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:23:49 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/18 16:21:50 by ffarah           ###   ########.fr       */
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
# include <time.h>
# include "def_vals.h"
# include "../mlx/mlx.h"
# include "get_next_line.h"
# include "vectors.h"
# include "objects.h"
# include "scene.h"
# include "intersection.h"
# include "parser.h"
# include "utils.h"
# include "ray_tracer.h"
# include "lights.h"
# include "bmpmake.h"
# define P_LIGHT 1
# define D_LIGHT 2
# define OBJ_SPHERE 1
# define INSIDE_OBJ -1
# define OBJ_PLANE 2
# define OBJ_SQUARE 3
# define OBJ_TRIAN 4
# define OBJ_CYL 5
# define OBJ_DISK 6
# define AMBIENT 1
# define DIRECT 2
# define POINTING 3
# define K_LAMB 0.4
# define K_SPEC 0.6
# define SIGMA 80

int				press_key(int key, t_scene *scene);
int				main(int ac, char **av);
#endif
