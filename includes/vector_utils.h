/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 14:08:11 by alex              #+#    #+#             */
/*   Updated: 2021/02/05 15:08:12 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_UTILS_H
# define VECTOR_UTILS_H
# include "minirt.h"

double			v_dot_product(t_vector *v1, t_vector *v2);
t_vector 		*v_cross_product(t_vector *v1, t_vector *v2);
int 			v_isnull(t_vector *v1);
t_vector		*v_cpy(t_vector *v);
t_point			*p_cpy(t_point *p);
#endif