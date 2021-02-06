/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 20:32:45 by alex              #+#    #+#             */
/*   Updated: 2021/02/06 20:56:24 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

void			parse_line(char *line, t_scene *scene);
void			parse_resolution(char *line, t_scene *scene);
t_point			*parse_point(char **line);
t_vector		*parse_vector(char **line);
t_color			*color_create(int r, int g, int b);
void			parse_cameras(char *line, t_scene *scene);
t_color			*parse_color_triplet(char **line);
void			parse_amb_light(char *line, t_scene *scene);
void			parse_lights(char *line, t_scene *scene);
t_object		*create_object(void *content, t_color *color,
								int type, t_ray *inter);
void			parse_sphere(char *line, t_scene *scene);
void		parse_plane(char *line, t_scene *scene);

#endif