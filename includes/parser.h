/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 20:32:45 by alex              #+#    #+#             */
/*   Updated: 2021/03/12 23:27:23 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "minirt.h"
t_vector		parse_point(char **line);
t_vector		parse_vector(char **line);
t_vector		parse_color_triplet(char **line);
t_object		*create_object(void *content, t_vector color, int type);
float			atof_modified(char **line);
float			ft_fabs(float value);
float			check_vector_input(t_vector *v);
void			error_throw(int a);
void			skip_spaces(char **line);
void			parse_line(char *line, t_scene *scene);
void			parse_plane(char *line, t_scene *scene);
void			parse_sphere(char *line, t_scene *scene);
void			parse_cameras(char *line, t_scene *scene);
void			parse_amb_light(char *line, t_scene *scene);
void			parse_resolution(char *line, t_scene *scene);
void			parse_input(t_scene *scene, int ac, char **av);
void			parse_lights(char *line, t_scene *scene, int type);
void			make_disk(t_cylinder *cy, t_vector col, t_scene *scene, int flag);
int				ft_isdigit(char ch);
int				ft_isspace(char ch);
int				atoi_modified(char **line);
#endif