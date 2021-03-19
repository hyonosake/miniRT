/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 13:07:59 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/19 15:19:56 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void			parse_square(char *line, t_scene *scene)
{
	t_square	*new;
	t_vector	col;

	if (!(new = (t_square *)malloc(sizeof(t_square))))
		error_throw(MALLOC_ERR);
	skip_spaces(&line);
	new->saved_orig = parse_point(&line);
	skip_spaces(&line);
	new->normal = parse_vector(&line);
	v_normalize(&new->normal);
	skip_spaces(&line);
	new->a = atof_modified(&line);
	printf("a = %.2f\n", new->a);
	new->ahalf = new->a * 0.5;
	skip_spaces(&line);
	col = parse_color_triplet(&line);
	print_vector(&col, "col:");
	skip_spaces(&line);
	if (*line != '\0' || !check_vector_input(&new->normal) ||
		new->a <= 0.0)
		error_throw(INPUT_ERR);
	add_object(scene, create_object((void *)new, col, SQUARE));
}

t_vector		get_tr_normal(t_trian *tr)
{
	t_vector	tmp[2];

	tmp[0] = v_sub(&tr->saved_p[0], &tr->saved_p[1]);
	tmp[1] = v_sub(&tr->saved_p[0], &tr->saved_p[2]);
	return (v_cross_product(&tmp[0], &tmp[1]));
}

void			parse_triangle(char *line, t_scene *scene)
{
	t_trian		*new;
	t_vector	col;

	if (!(new = (t_trian *)malloc(sizeof(t_trian))))
		error_throw(MALLOC_ERR);
	skip_spaces(&line);
	new->saved_p[0] = parse_point(&line);
	skip_spaces(&line);
	new->saved_p[1] = parse_point(&line);
	skip_spaces(&line);
	new->saved_p[2] = parse_point(&line);
	skip_spaces(&line);
	col = parse_color_triplet(&line);
	skip_spaces(&line);
	if (*line != '\0')
		error_throw(INPUT_ERR);
	new->normal = get_tr_normal(new);
	v_normalize(&new->normal);
	add_object(scene, create_object((void *)new, col, TRIAN));
}

void			parse_sphere(char *line, t_scene *scene)
{
	t_sphere	*new;
	t_vector	col;

	if (!(new = (t_sphere *)malloc(sizeof(t_sphere))))
		error_throw(MALLOC_ERR);
	skip_spaces(&line);
	new->saved_orig = parse_point(&line);
	skip_spaces(&line);
	new->r = atof_modified(&line) / 2;
	skip_spaces(&line);
	col = parse_color_triplet(&line);
	skip_spaces(&line);
	new->rsq = pow(new->r, 2);
	new->is_inside = 0;
	if (*line != '\0' || new->r <= 0)
		error_throw(INPUT_ERR);
	add_object(scene, create_object((void *)new, col, SPHERE));
}

void			parse_plane(char *line, t_scene *scene)
{
	t_plane		*new;
	t_vector	col;

	if (!(new = (t_plane *)malloc(sizeof(t_plane))))
		error_throw(MALLOC_ERR);
	skip_spaces(&line);
	new->saved_orig = parse_point(&line);
	skip_spaces(&line);
	new->normal = parse_vector(&line);
	v_normalize(&new->normal);
	skip_spaces(&line);
	col = parse_color_triplet(&line);
	skip_spaces(&line);
	if (*line != '\0' || !check_vector_input(&new->normal))
		error_throw(INPUT_ERR);
	add_object(scene, create_object((void *)new, col, PLANE));
}
