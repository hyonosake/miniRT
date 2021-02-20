/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 11:56:01 by alex              #+#    #+#             */
/*   Updated: 2021/02/21 02:45:11 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

double			return_min_positive(double r1, double r2, double min_t)
{
	if (r1 < 0 || r2 < 0)
		return (min_t);
	if (r1 > 0 && r1 <= r2)
		return (r1);
	else if (r2 > 0 && r2 < r1)
		return (r2);
	return (min_t);
}

double			sphere_intersection(t_ray *ray, t_sphere *sp, double min_t)
{
	double		coeffs[3];
	double		det;
	double		ret_val;
	t_vector	*centers;

	centers = v_from_p(sp->orig, ray->orig);
	coeffs[0] = 1;
	coeffs[1] = 2 * v_dot_product(centers, ray->dir);
	coeffs[2] = v_dot_product(centers, centers) - sp->rsq;
	det = pow(coeffs[1], 2) - 4 * coeffs[0] * coeffs[2];
	if (det < 0)
		return (min_t);
	ret_val = return_min_positive(
		(-coeffs[1] + sqrt(det)) / (2 * coeffs[0]),
		(-coeffs[1] - sqrt(det)) / (2 * coeffs[0]), min_t);
	free(centers);
	return (ret_val);
}

t_intersect		*init_sphere(t_sphere *sphere, double res, t_ray *ray, t_color *col)
{
	t_intersect	*ans;

	if (!(ans = (t_intersect *)malloc(sizeof(t_intersect))))
		error_throw(-1);
	ans->color = col;
	ans->res = res;
	ans->p_inter = p_from_v(ray->dir, res);
	ans->to_cam = v_by_scalar(ray->dir, -1);
	ans->normal = v_from_p(sphere->orig, ans->p_inter);
	v_normalize(ans->normal);
	return (ans);
}

t_intersect		*init_plane(t_plane *pl, double res, t_ray *ray, t_color *col)
{
	t_intersect	*ans;

	if (!(ans = (t_intersect *)malloc(sizeof(t_intersect))))
		error_throw(-1);
	ans->res = res;
	ans->color = col;
	ans->p_inter = p_from_v(ray->dir, res);
	ans->to_cam = v_by_scalar(ray->dir, -1);
	ans->normal = v_cpy(pl->normal);
	v_normalize(ans->normal);
	v_normalize(ans->to_cam);
	return (ans);	
}

t_intersect		*init_objects(t_object *object, double res, t_ray *ray)
{
	t_intersect	*ans;
	if (!object || res == MAX)
		return NULL;
	if (object->type == OBJ_SPHERE)
		ans = init_sphere((t_sphere *)object->content, res, ray, object->color);
	else if (object->type == OBJ_PLANE)
		ans = init_plane((t_plane *)object->content, res, ray, object->color);
	else
		ans = NULL;
	return (ans);
}

double			plane_intersection(t_plane *plane, double min_t, t_ray *ray)
{
	t_vector	*tmp;
	double		coeffs[2];
	double		res;

	tmp = v_from_p(ray->orig, plane->orig);
	coeffs[0] = v_dot_product(tmp, plane->normal);
	free(tmp);
	coeffs[1] = v_dot_product(ray->dir, plane->normal);
	if (!coeffs[1])
		coeffs[1] = 0.000001;
	res = coeffs[0] / coeffs[1];
	if (res < min_t) 
		return (res);
	return (min_t);
}



double			dots_in_square(t_square *square, int type, t_point *q)
{
	double		res;
	t_vector	*p_q;
	t_point		*p;

	if (type == 12)
	{
		p = v_from_values(square->v12->xv - square->a / 2, square->v12->yv, square->v12->zv);
		p_q = v_from_p(q, p);
		return (v_dot_product(p_q, square->v12));
	}
	if (type == 23)
	{
		p = v_from_values(square->v23->xv - square->a / 2, square->v23->yv + square->a / 2, square->v23->zv);
		p_q = v_from_p(q, p);
		return (v_dot_product(p_q, square->v23));
	}
	if (type == 34)
	{
		p = v_from_values(square->v34->xv - square->a / 2, square->v34->yv - square->a / 2, square->v34->zv);
		p_q = v_from_p(q, p);
		return (v_dot_product(p_q, square->v34));
	}
	if (type == 41)
	{
		p = v_from_values(square->v12->xv - square->a / 2, square->v12->yv - square->a / 2, square->v41->zv);
		p_q = v_from_p(q, p);
		return (v_dot_product(p_q, square->v41));
	}
	free(p_q);
	free(p);
}


int			check_point_in_square(t_square *square, double min_t, double res, t_point *q);
{
	//t_vector	*p_q;
	//t_point		*p;
	double		vals[4];
	int			sign;

	p = v_from_values(square->v12->x - a /2, square->v12->y, square->v12->z);
	p_q = v_from_p(q, p);
	vals[0] = v_dot_product(p_q, v12);
	free(p);
	free(pq);
	p = v_from_values(square->v12->x - a /2, square->v12->y, square->v12->z);
	p_q = v_from_p(q, p);
	vals[1] = v_dot_product(p_q, v23);
	vals[2] = v_dot_product(p_q, v34);
	vals[3] = v_dot_product(p_q, v23);
	
	

	return 0;
}

double			*coord_init(int type, double a)
{
	double		coords[3];

	if (type == 12)
	{
		coords[0] = -a;
		coords[1] = 0;
	}
	if (type == 23)
	{
		coords[0] = 0;
		coords[1] = -a;
	}
	if (type == 34)
	{
		coords[0] = a;
		coords[1] = 0;
	}
	if (type == 41)
	{
		coords[0] = 0;
		coords[1] = a;
	}
	coords[2] = 0;
	return (&coords);
}

double			square_intersection(t_square *square, double min_t, t_ray *ray)
{
	double		res;
	t_point		*check;
	t_vector	**vectors;
	t_basis		*fo_sq;

	if ((res = plane_intersection((t_plane *)square, min_t, ray) < min_t))
	{
		fo_sq = basis_init(square->normal);
		square->v12 = v_from_basis(fo_sq, coord_init(12, square->a));
		square->v23 = v_from_basis(fo_sq, coord_init(23, square->a));
		square->v34 = v_from_basis(fo_sq, coord_init(34, square->a));
		square->v41 = v_from_basis(fo_sq, coord_init(41, square->a));
		check = v_by_scalar(ray->dir, res);
	}
	
	//basis_free(fo_sq);
	return (res);
}

t_intersect		*ray_objects_intersection(t_object *objs, t_ray *ray)
{
	t_object	*tmp;
	double		res;
	double		min_t;
	t_object	*ans;

	min_t = MAX;
	tmp = objs;
	ans = NULL;
	res = min_t;
	while (tmp)
	{
		if (tmp->type == OBJ_SPHERE)
			res = sphere_intersection(ray, (t_sphere *)tmp->content, min_t);
		else if (tmp->type == OBJ_PLANE)
			res = plane_intersection((t_plane *)tmp->content, min_t, ray);
		else if (tmp->type == OBJ_SQUARE)
			res = square_intersection((t_square *)tmp->content, min_t, ray);
		else
			printf("noooo way ;( \n");
		if (res < min_t && res > 0.001)
		{
			min_t = res;
			ans = tmp;
		}
		tmp = tmp->next;
	}
	return (init_objects(ans, min_t, ray));
}
