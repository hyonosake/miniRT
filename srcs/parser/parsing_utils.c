/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 19:51:59 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/20 01:12:00 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include <ctype.h>

t_object			*create_object(void *content, t_vector color, int type)
{
	t_object		*new;

	if (!(new = (t_object *)malloc(sizeof(t_object))))
		error_throw(MALLOC_ERR);
	new->type = type;
	new->content = content;
	new->color = color;
	new->next = NULL;
	return (new);
}

float				ft_fabs(float value)
{
	if (value < 0)
		value *= -1;
	return (value);
}

float				check_vector_input(t_vector *v)
{
	if (ft_fabs(v->xv) > 1 ||
		ft_fabs(v->yv) > 1 ||
		ft_fabs(v->zv) > 1)
		return (0);
	return (1);
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
