/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_atof.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 22:02:49 by alex              #+#    #+#             */
/*   Updated: 2021/03/20 03:08:21 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int					define_sign(char **s)
{
	int				sign;

	sign = 1.0;
	if (**s == '+' || **s == '-')
	{
		if (**s == '-')
		{
			sign *= (-1);
		}
		++(*s);
	}
	return (sign);
}

int					atoi_modified(char **line)
{
	int				result;

	result = 0;
	skip_spaces(line);
	while (ft_isdigit(**line))
	{
		result = result * 10 + (**line - '0');
		++(*line);
	}
	return (result);
}

float				atof_modified(char **line)
{
	float			result;
	float			m_power;
	float			sign;

	m_power = 0.1;
	sign = define_sign(line);
	result = atoi_modified(line);
	if (**line == ',' || !**line || ft_isspace(**line))
		return ((float)result * sign);
	else if (**line != '.')
		error_throw(INPUT_ERR);
	++(*line);
	while (ft_isdigit(**line))
	{
		result += (**line - '0') * m_power;
		m_power *= 0.1;
		++(*line);
	}
	return (sign * ((float)result));
}

t_vector			parse_point(char **line)
{
	float			index[3];

	skip_spaces(line);
	index[0] = atof_modified(line);
	skip_spaces(line);
	if (**line != ',')
		error_throw(INPUT_ERR);
	++(*line);
	skip_spaces(line);
	index[1] = atof_modified(line);
	skip_spaces(line);
	if (**line != ',')
		error_throw(INPUT_ERR);
	++(*line);
	skip_spaces(line);
	index[2] = atof_modified(line);
	if (**line && !(ft_isspace(**line)))
		error_throw(INPUT_ERR);
	return (v_from_values(index[0], index[1], index[2]));
}

t_vector		parse_color_triplet(char **line)
{
	float		rgb[3];
	t_vector	rgb_v;

	if (**line == ',')
		error_throw(INPUT_ERR);
	rgb[0] = 1.0 * atoi_modified(line) * VECTORIZE_COLOR;
	skip_spaces(line);
	if (**line != ',')
		error_throw(INPUT_ERR);
	++(*line);
	rgb[1] = 1.0 * atoi_modified(line) * VECTORIZE_COLOR;
	skip_spaces(line);
	if (**line != ',')
		error_throw(INPUT_ERR);
	++(*line);
	skip_spaces(line);
	rgb[2] = 1.0 * atoi_modified(line) * VECTORIZE_COLOR;
	rgb_v = v_from_values(rgb[0], rgb[1], rgb[2]);
	if (**line || !check_vector_input(&rgb_v))
		error_throw(INPUT_ERR);
	return (rgb_v);
}
