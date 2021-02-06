/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 22:02:07 by alex              #+#    #+#             */
/*   Updated: 2021/02/06 20:15:26 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_UTILS_H
# define PARSING_UTILS_H
int		ft_isdigit(char ch);
void	skip_spaces(char **line);
int		ft_isspace(char ch);
int		atoi_modified(char **line);
double	atof_modified(char **line);

#endif