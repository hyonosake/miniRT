/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 22:13:30 by ffarah            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/03/14 16:41:05 by alex             ###   ########.fr       */
=======
/*   Updated: 2021/03/13 00:35:55 by ffarah           ###   ########.fr       */
>>>>>>> b77465c3407587569c1b46e3c26daffd3b3b0b4d
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_vector		create_normal(t_cylinder *cy, float res, t_ray *ray)
{
	t_vector	tau;
	t_vector	ap;
	t_vector	op;

	op = point_from_vector(&ray->dir, res);
	ap = v_sub(&cy->orig, &ray->orig);
	ap = v_sub(&ap, &op);
	tau = v_cross_product(&cy->axis, &ap);
	return(v_cross_product(&cy->axis, &tau));
}


float			check_cylinder_output(t_cylinder *cy,float min_t, t_ray *ray)
{
	float		dots[2];
	t_vector	ap;
	float		ret_val;
	//check for t1 first
	ret_val = min_t;
	ap = point_from_vector(&ray->dir, cy->t[0]);
	dots[0] = ft_fabs(v_dot_product(&cy->axis, &ap));
	if (dots[0] > cy->len * 0.5)
		dots[0] = -1;
	ap = point_from_vector(&ray->dir, cy->t[1]);
	dots[1] = ft_fabs(v_dot_product(&cy->axis, &ap));
	if (dots[1] > cy->len * 0.5)
		dots[0] = -1;
	if (dots[0] > 0 && dots[1] > 0)
	{
		//printf("Am i a joke to you?\n");
		ret_val = return_min_positive(cy->t[0], cy->t[1], min_t);
		cy->norm = create_normal(cy, ret_val, ray);
	}
	//else if (dots[0] < 0 && dots[1] < 0)
	//	ret_val = min_t;
	return (ret_val);
}



float			cylinder_intersection(t_cylinder *cy, t_ray *ray, float min_t)
{
	float		a;
	float		b;
	float		c;
	float		det;
	t_vector	co;
<<<<<<< HEAD
	t_vector	cp;
	//a = v_dot_product(&ray->dir, &ray->dir) *
	// print_vector(&cy->orig, "cy");
=======
	//t_vector	cp;
	//print_vector(&ray->dir, "ray->dir");
>>>>>>> b77465c3407587569c1b46e3c26daffd3b3b0b4d
	co = v_sub(&cy->orig, &ray->orig);
	a = v_dot_product(&ray->dir, &cy->axis) * v_dot_product(&ray->dir, &cy->axis) - 1;
	b = 2 * (v_dot_product(&co, &cy->axis) * v_dot_product(&ray->dir, & cy->axis) -
			v_dot_product(&ray->dir, &co));
	c = v_dot_product(&co, &cy->axis) * v_dot_product(&co, &cy->axis) + cy->rsq - co.mod * co.mod; //???
	det = b * b - 4 * a * c;
	if (ray->dir.xv == 0 && ray->dir.yv == 0 && ray->dir.zv == -1)
	{
		printf("once in a lifetime\n");
		print_vector(&ray->dir, "r_d");
		print_vector(&cy->axis, "axiss");
		print_vector(&co, "CO");
		printf("r = %.2f = %.2f\n", cy->r, cy->rsq);
		printf("det = %.2f\n", det);
		printf("ray->dir * cy->axis = %.2f\n", v_dot_product(&ray->dir, &cy->axis));
		printf("a = %.2f\nb = %.2f\nc = %.2f\n", a, b, c);
		printf("[%.2f %.3f]\n", cy->t[0], cy->t[1]);
	}
	if (det < 0)
		return (min_t);
	cy->t[0] = (- b + sqrt(det) ) / (2 * a);
	cy->t[1] = (- b - sqrt(det) ) / (2 * a);
	//if (cy->t[0] < MIN && cy->t[1] < MIN)	
	//	return (min_t);
	//return (check_cylinder_output(cy, min_t, ray));
	float ret_val = return_min_positive(cy->t[0], cy->t[1], min_t);
	printf("I should ret %.2f\n", ret_val);
	cy->norm = create_normal(cy, ret_val, ray);
	return (return_min_positive(cy->t[0], cy->t[1], min_t));
}


t_intersect		*init_cylinder(t_object *cy, float res, t_ray *ray)
{
	t_intersect	*ans;

	if (!(ans = (t_intersect *)malloc(sizeof(t_intersect))))
		error_throw(-1);
	ans->color = cy->color;
	ans->res = res;
	ans->p_inter = point_from_vector(&ray->dir, res);
	//ans->normal = v_sub(&((t_cylinder *)cy->content)->orig, &ans->p_inter);
	//printf("\n---------------\n");
	//print_vector(&ans->normal, "norm:");
	ans->normal = ((t_cylinder *)cy->content)->norm;
	//print_vector(&ans->normal, "norm:");
	//printf("\n---------------\n");
	if (cy->type == INSIDE_OBJ)
	{
		cy->type = OBJ_CYL;
		v_by_scalar(&ans->normal, -1);
	}
	ans->to_cam = point_from_vector(&ray->dir, -1);
	ans->type = cy->type;
	return (ans);
}