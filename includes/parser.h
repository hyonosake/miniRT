/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 20:32:45 by alex              #+#    #+#             */
/*   Updated: 2021/02/06 03:11:45 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

void			parse_line(char *line, t_scene *scene);
void			add_canvas(t_scene *scene, t_canvas *new);
void			parse_resolution(char *line, t_scene *scene);
void			parse_cameras(char *line, t_scene *scene);
void			add_camera(t_scene *scene, t_camera *cam);

#endif