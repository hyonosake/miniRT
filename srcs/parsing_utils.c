/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 22:02:49 by alex              #+#    #+#             */
/*   Updated: 2021/02/06 15:29:41 by alex             ###   ########.fr       */
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

int		atoi_modified(char **line)
{
	int	result;
	int	sign;

	sign = 1;
	result = 0;  
	while (ft_isdigit(**line))
	{
		result = result * 10 + (**line - '0');
		*line += 1;
	}
	return(result * sign);
}

int ft_isspace(char ch)
{
	if ((ch > 8 && ch< 14) || ch == 32)
		return 1;
	return 0;
}
double	atof_modified(char **line)
{
	long long int	parts[2];
	int				flag;
	int				power;
	double			min;
	power = 0;
	flag = 1;
	min = 1.0;
	if (**line == '+' || **line == '-')
	{
		if (**line  == '-')
			min *= (-1);
		*line += 1;
	}
	parts[0] = atoi_modified(line);
	if (**line != '.' && **line != ',' && !ft_isspace(**line))
		error_throw(-2);
	if (**line == ',')
		return ((double)parts[0]);
	*line += 1;
	flag = 1;
	parts[1] = 0;
	while (ft_isdigit(**line))
	{
		parts[1]= parts[1] * 10 + (**line - '0');
		*line += 1;
		power += 1;
	}
	return (min * ((double)parts[0] + (double)parts[1] / pow(10, power)));
}

