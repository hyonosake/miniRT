/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 09:47:27 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/18 15:46:24 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>

char	*ft_strjoin(char *orig, char *to_add);
char	*ft_line_fill(char *rem, int endl_index);
char	*ft_make_left_pretty(char *rem, int endl_index);
int		ft_free(char *res);
int		ft_strlen(char *s);
int		ft_endl_index(char *s);
int		get_next_line(int fd, char **line);
int		ft_strcmp(char *s1, char *s2, int n);

#endif

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 64
#endif
