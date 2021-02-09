/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 19:25:48 by alex              #+#    #+#             */
/*   Updated: 2021/02/08 19:53:20 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int			bitshift_me_please(t_color *color)
{
	int ans = color->r << 16 | color->g << 8 | color->b;
	printf("[%i %i %i]\n", color->r, color->g, color->b);
	printf("ans = %d\n", ans);
	return (ans);
}

int			intensity_and_color(t_color *color, double intensity)
{
	int ans;
	int rgb[3];

	rgb[0] = color->r * intensity;
	rgb[1] = color->g * intensity;
	rgb[2] = color->b * intensity;
	ans = rgb[0] << 16 | rgb[1] << 8 | rgb[2];
	return (ans);
}

double		return_min_positive(double r1, double r2)
{
	if (r1 < 0 || r2 < 0)
		return (0);
	if (r1 > 0 && r1 <= r2)
		return (r1);
	else if (r2 > 0 && r2 < r1)
		return (r2);
	return (0);
}

void				sphere_intersection(t_ray *ray, t_sphere *sp, t_trace *ans, t_color *color)
{
	double	res[2];
	double	coeffs[3];
	double	det;
	double	ret_val;

	t_vector *centers = v_from_p(ray->orig, sp->orig);
	coeffs[0] = v_dot_product(ray->dir, ray->dir);
	coeffs[1] = 2 * v_dot_product(centers, ray->dir);
	coeffs[2] = v_dot_product(centers, centers) - sp->rsq;
	det = pow(coeffs[1], 2) - 4 * coeffs[0] * coeffs[2];
	if (det < 0)
		return ;
	res[0] = (- coeffs[1] + sqrt(det)) / (2 * coeffs[0]);
	res[1] = (- coeffs[1] - sqrt(det)) / (2 * coeffs[0]);
	ret_val = return_min_positive(res[0], res[1]);
	//printf("[%.3f %.3f]\n", res[0], res[1]);
	if (ret_val != 0 && ret_val < ans->solution)
	{
		ans->solution  = ret_val;
		ans->p_intersect = p_from_v(ray->dir, ret_val);
		ans->normal = v_from_p(ans->p_intersect, sp->orig);
		ans->col = color;
		v_normalize(ans->normal);
	}
	free(centers);
	
}

t_trace 		*ray_objects_intersection(t_object *objs, t_ray *ray)
{
	t_object	*tmp;
	double		res;
	t_trace		*ans;
	
	tmp = objs;
	ans = (t_trace *)malloc(sizeof(t_trace));
	ans->solution = MAX;
	ans->p_intersect = NULL;
	ans->normal = NULL;
	ans->view = v_by_scalar(ray->dir, -1);
	ans->bisect = NULL;
	ans->obj = NULL;
	ans->col = NULL;
	while (tmp)
	{
		if (tmp->type == OBJ_SPHERE)
		{
			sphere_intersection(ray, (t_sphere *)tmp->content, ans, tmp->color);
			ans->obj = tmp;
			//printf("ans = %.3f\n", ans->solution);
			//print_color(ans->col);
		}
		else
			printf("noooo way ;( \n");
		tmp = tmp->next;
	}
	if (ans->solution == MAX)
	{
		free(ans);
		return (NULL);
	}
	return (ans);
}
