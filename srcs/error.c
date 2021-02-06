/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 01:35:20 by ffarah            #+#    #+#             */
/*   Updated: 2021/02/06 01:54:19 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void error_throw(int erno)
{
	if (erno == -1)
		write(1, "ERROR during memory allocation. Aborting\n", 42);
	if (erno == -2)
		write(1, "ERROR. Invalid input. Aborting\n", 32);
	exit(erno);
}
