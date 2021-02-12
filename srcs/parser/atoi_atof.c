/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_atof.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 22:02:49 by alex              #+#    #+#             */
/*   Updated: 2021/02/12 20:03:19 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

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
		{
			min *= (-1);
		}
		++(*line);
	}
	parts[0] = atoi_modified(line);
	if (**line == ',' || !**line || ft_isspace(**line))
		return ((double)parts[0] * min);
	else if (**line != '.')
		error_throw(-2);
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
