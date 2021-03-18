/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 19:51:59 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/18 15:35:27 by ffarah           ###   ########.fr       */
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

t_vector			parse_vector(char **line)
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
	if (**line && **line != '\t' && **line != ' ')
		error_throw(INPUT_ERR);
	return (v_from_values(index[0], index[1], index[2]));
}

float				ft_fabs(float value)
{
	if (value < 0)
		value *= -1;
	return (value);
}

float				check_vector_input(t_vector *v)
{
	if (ft_fabs(v->xv) > 1 || ft_fabs(v->yv) > 1 || ft_fabs(v->zv) > 1)
		return (0);
	if (ft_fabs(v->xv) < -1 || ft_fabs(v->yv) < -1 || ft_fabs(v->zv) < -1)
		return (0);
	return (1);
}
