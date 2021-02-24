/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 19:51:59 by ffarah            #+#    #+#             */
/*   Updated: 2021/02/24 13:50:10 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include <ctype.h>

void			skip_spaces(char **line)
{
	while (**line == ' ' || **line == '\t')
		++(*line);
}

int				ft_isdigit(char ch)
{
	if (ch >= '0' && ch <= '9')
		return (1);
	return (0);
}

int				ft_isspace(char ch)
{
	if (ch == ' ' || ch == '\t')
		return (1);
	return (0);
}


int				atoi_modified(char **line)
{
	int	result;

	result = 0; 
	skip_spaces(line);
	while (ft_isdigit(**line))
	{
		result = result * 10 + (**line - '0');
		++(*line);
	}
	return(result);
}

t_point			*parse_point(char **line)
{
	double	index[3];

	skip_spaces(line);
	index[0] = atof_modified(line);
	skip_spaces(line);
	if (**line != ',')
	{
		error_throw(-2);
		//printf("here\n");
	}
	++(*line);
	skip_spaces(line);
	index[1] = atof_modified(line);
	skip_spaces(line);
	if (**line != ',')
		error_throw(-2);
	++(*line);
	skip_spaces(line);
	index[2] = atof_modified(line);
	if (**line && !(ft_isspace(**line)))
		error_throw(-2);
	return (p_from_values(index[0], index[1], index[2]));
}

t_vector	*parse_vector(char **line)
{
	double	index[3];

	skip_spaces(line);
	index[0] = atof_modified(line);
	skip_spaces(line);
	if (**line != ',')
		error_throw(-2);
	++(*line);
	skip_spaces(line);
	index[1] = atof_modified(line);
	skip_spaces(line);
	if (**line != ',')
		error_throw(-2);
	++(*line);
	skip_spaces(line);
	index[2] = atof_modified(line);
	if (**line && **line != '\t' && **line != ' ')
		error_throw(-2);
	return (v_from_values(index[0], index[1], index[2]));
}