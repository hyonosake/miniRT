/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 20:33:38 by alex              #+#    #+#             */
/*   Updated: 2021/02/12 11:16:59 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_color		*color_create(int r, int g, int b)
{
	t_color	*new;
	
	if(!(new = (t_color *)malloc(sizeof(t_color))))
		error_throw(-1);
	if (r > 255 || r < 0 || g > 255 || g < 0 ||
		b > 255 || b < 0)
		error_throw(-2);
	new->r = r;
	new->g = g;
	new->b = b;
	return (new);
}