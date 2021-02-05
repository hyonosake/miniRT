/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 22:02:49 by alex              #+#    #+#             */
/*   Updated: 2021/02/05 22:37:47 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int		ft_isdigit(char ch)
{
	if (ch >= '0' && ch <= '9')
		return (1);
	return (0);
}

int		atoi_modified(char **line)
{
	int	result;
	int	sign;
	int i;

	sign = 1;
	result = 0;
	while (**line == '+' || **line == '-')
	{
		if (**line  == '-')
			sign *= (-1);
		*(line++);
	}
	while (ft_isdigit(**line))
	{
		printf("%c\n", **line);
		result = result * 10 + (**line - '0');
		*(line++);
	}
	return(result * sign);
}