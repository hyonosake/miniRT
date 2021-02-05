/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 20:33:35 by alex              #+#    #+#             */
/*   Updated: 2021/02/05 20:54:58 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void		parse_line(char *line)
{
	if (!line)
		error_throw(-2);
	if (line[0] == 'R' && (line++))
		parse_resolution(line);
}


void	parse_resolution(char *line)
{
	t_canvas	*new;
	
	if(!(new = (t_canvas *)malloc(sizeof(t_canvas))))
		error_throw(-1);
	// parse_int()
	// //while()
}