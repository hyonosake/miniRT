/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 14:08:11 by alex              #+#    #+#             */
/*   Updated: 2021/02/08 19:33:13 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_UTILS_H
# define VECTOR_UTILS_H
# include "minirt.h"

double			v_dot_product(t_vector *v1, t_vector *v2);
t_vector 		*v_cross_product(t_vector *v1, t_vector *v2);
t_vector		*v_by_scalar(t_vector *v1, double d);
int 			v_isnull(t_vector *v1);
t_vector		*v_cpy(t_vector *v);
t_point			*p_cpy(t_point *p);
t_point		*p_from_string(char **line);
t_vector	*v_from_string(char **line);
void		v_normalize(t_vector *v);
t_point		*p_from_v(t_vector *v, double c);
t_vector	*v_add(t_vector *v1, t_vector *v2);
#endif