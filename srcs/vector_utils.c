/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 14:14:19 by alex              #+#    #+#             */
/*   Updated: 2021/02/06 03:30:17 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

double			v_dot_product(t_vector *v1, t_vector *v2)
{
	double result;
	result = v1->xv * v2->xv + v1->yv * v2->yv + v1->zv * v2->zv;
	return (result);
}

t_vector 		*v_cross_product(t_vector *v1, t_vector *v2)
{
	t_vector	*new;

	new = v_from_values(0,0,0);
	new->xv = v1->yv * v1->zv -	v1->zv * v1->yv;
	new->yv = v1->zv * v1->xv -	v1->xv * v1->zv;
	new->zv = v1->xv * v1->yv -	v1->yv * v1->xv;
	new->mod = sqrt(v_dot_product(new,new));
	return (new);
}

t_vector		*v_by_scalar(t_vector *v1, double d)
{
	t_vector	*new;
	new = v_from_values(0,0,0);
	new->xv = v1->xv * d;
	new->yv = v1->yv * d;
	new->zv = v1->zv * d;
	new->mod = sqrt(v_dot_product(new, new));
	return (new);
}

int 			v_isnull(t_vector *v1)
{
	if (!v1->xv && !v1->yv && !v1->zv)
		return (1);
	return (0);
}

t_vector		*v_cpy(t_vector *v)
{
	return(v_from_values(v->mod, v->yv, v->zv));
}

t_point			*p_cpy(t_point *p)
{
	return (p_from_values(p->xp, p->yp, p->zp));
}

t_point		*p_from_string(char **line)
{
	double	c[3];

	c[0] = atof_modified(line);
	if (**line != ',')
		error_throw(-2);
	++(*line);
	skip_spaces(line);
	c[1] = atof_modified(line);
	if (**line != ',')
		error_throw(-2);
	++(*line);
	skip_spaces(line);
	c[2] = atof_modified(line);
	return(p_from_values(c[0], c[1], c[2]));	
}

t_vector	*v_from_string(char **line)
{
	double	c[3];

	c[0] = atof_modified(line);
	printf("1. standing on %c\n", **line);
	if (**line != ',')
		error_throw(-2);
	++(*line);
	printf("2. standing on %c\n", **line);
	skip_spaces(line);
	printf("3. standing on %c\n", **line);
	c[1] = atof_modified(line);
	printf("4. standing on %c\n", **line);
	if (**line != ',')
		error_throw(-2);
	++(*line);
	skip_spaces(line);
	printf("[%f %f %f]\n", c[0], c[1], c[2]);
	c[2] = atof_modified(line);
	printf("here\n");
	return(v_from_values(c[0], c[1], c[2]));	
}