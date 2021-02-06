/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 20:32:45 by alex              #+#    #+#             */
/*   Updated: 2021/02/06 15:43:45 by alex             ###   ########.fr       */
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



#endif