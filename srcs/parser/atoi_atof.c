/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_atof.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 22:02:49 by alex              #+#    #+#             */
/*   Updated: 2021/03/18 16:17:34 by ffarah           ###   ########.fr       */
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

void				skip_spaces(char **line)
{
	while (**line == ' ' || **line == '\t')
		++(*line);
}

int					ft_isdigit(char ch)
{
	if (ch >= '0' && ch <= '9')
		return (1);
	return (0);
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
	long long int	parts[2];
	int				flag;
	int				power;
	float			min;

	power = 0;
	flag = 1;
	min = define_sign(line);
	parts[0] = atoi_modified(line);
	if (**line == ',' || !**line || ft_isspace(**line))
		return ((float)parts[0] * min);
	else if (**line != '.')
		error_throw(INPUT_ERR);
	*line += 1;
	flag = 1;
	parts[1] = 0;
	while (ft_isdigit(**line))
	{
		parts[1] = parts[1] * 10 + (**line - '0');
		*line += 1;
		power += 1;
	}
	return (min * ((float)parts[0] + (float)parts[1] / pow(10, power)));
}
