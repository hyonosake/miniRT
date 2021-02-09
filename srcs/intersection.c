///* ************************************************************************** */
///*                                                                            */
///*                                                        :::      ::::::::   */
///*   intersection.c                                     :+:      :+:    :+:   */
///*                                                    +:+ +:+         +:+     */
///*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
///*                                                +#+#+#+#+#+   +#+           */
///*   Created: 2021/02/08 19:25:48 by alex              #+#    #+#             */
///*   Updated: 2021/02/09 17:38:10 by ffarah           ###   ########.fr       */
///*                                                                            */
///* ************************************************************************** */

//#include "../includes/minirt.h"

//int			bitshift_me_please(t_color *color)
//{
//	int ans = color->r << 16 | color->g << 8 | color->b;
//	printf("[%i %i %i]\n", color->r, color->g, color->b);
//	printf("ans = %d\n", ans);
//	return (ans);
//}

//int			intensity_and_color(t_color *color, double intensity)
//{
//	int ans;
//	int rgb[3];

//	rgb[0] = color->r * intensity;
//	rgb[1] = color->g * intensity;
//	rgb[2] = color->b * intensity;
//	ans = rgb[0] << 16 | rgb[1] << 8 | rgb[2];
//	return (ans);
//}

//double		return_min_positive(double r1, double r2)
//{
//	if (r1 < 0 || r2 < 0)
//		return (0);
//	if (r1 > 0 && r1 <= r2)
//		return (r1);
//	else if (r2 > 0 && r2 < r1)
//		return (r2);
//	return (0);
//}

//double		sphere_intersection(t_ray *ray, t_sphere *sp, double min_t)
//{
//	double	res[2];
//	double	coeffs[3];
//	double	det;
//	double	ret_val;

//	t_vector *centers = v_from_p(ray->orig, sp->orig);
//	coeffs[0] = v_dot_product(ray->dir, ray->dir);
//	coeffs[1] = 2 * v_dot_product(centers, ray->dir);
//	coeffs[2] = v_dot_product(centers, centers) - sp->rsq;
//	det = pow(coeffs[1], 2) - 4 * coeffs[0] * coeffs[2];
//	if (det < 0)
//		return (min_t);
//	res[0] = (- coeffs[1] + sqrt(det)) / (2 * coeffs[0]);
//	res[1] = (- coeffs[1] - sqrt(det)) / (2 * coeffs[0]);
//	ret_val = return_min_positive(res[0], res[1]);
//	free(centers);
//	if (ret_val != 0 && ret_val < min_t)
//		return (ret_val);
//	return (min_t);
//}

//t_object		*ray_objects_intersection(t_object *objs, t_ray *ray)
//{
//	t_object	*tmp;
//	double		res;
//	double		min_t;
//	t_object	*ans;

//	min_t = MAX;
//	tmp = objs;
//	ans = (t_object *)malloc(sizeof(t_object));
//	ans->type = 0;
//	ans->content = NULL;
//	ans->intersection = NULL;
//	ans->color = NULL;
//	while (tmp)
//	{
//		if (tmp->type == OBJ_SPHERE)
//		{
//			res = sphere_intersection(ray, (t_sphere *)tmp->content, min_t);
//			if (res < min_t)
//			{
//				res = min_t;
//				ans = tmp;
//				ans->intersection->orig = p_from_v(ray->dir, res);
//				ans->intersection->dir = v_from_p(ans->intersection->orig,
//						((t_sphere *)tmp->content)->orig);
//				v_normalize(ans->intersection->dir);
//			}	
//		}
//		else
//			printf("noooo way ;( \n");
//		tmp = tmp->next;
//	}
//	if (min_t == MAX)
//	{
//		free(ans);
//		return (NULL);
//	}
//	return (ans);
//}
