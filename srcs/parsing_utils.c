/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 19:51:59 by ffarah            #+#    #+#             */
/*   Updated: 2021/02/06 19:52:50 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int		ft_isdigit(char ch)
{
	if (ch >= '0' && ch <= '9')
		return (1);
	return (0);
}

void		skip_spaces(char **line)
{
	while ((**line > 8 && **line < 14) || **line == 32)
		++(*line);
}

int ft_isspace(char ch)
{
	if ((ch > 8 && ch< 14) || ch == 32)
		return 1;
	return 0;
}

t_vector			*parse_vector(char **line)
{
	t_vector		*new;
	skip_spaces(line);
	new = v_from_string(line);
	skip_spaces(line);
	return (new);
}

t_point			*parse_point(char **line)
{
	t_point		*new;
	skip_spaces(line);
	new = p_from_string(line);
	skip_spaces(line);
	return (new);
}