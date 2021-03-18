/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 09:07:26 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/17 18:16:13 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTS_H
# define LIGHTS_H

typedef struct			s_l_comp
{
	t_vector			obj_color;
	t_vector			l_color;
	t_vector			amb_color;
	t_vector			to_light;
	t_vector			diffuse;
	t_vector			spec;
	t_vector			total_coeffs;
	t_vector			total_color;
	float				k_light;
	float				k_amb;
	float				k_diff;
	float				k_spec;	
	float				k_fading;			
	char				l_type;
}						t_l_comp;

t_vector			color_multiply(t_vector *v1, t_vector *v2, double k);
int					shadows(t_object *objs, t_ray *ray, float min_t);
float				return_max_positive(float c);
void				turn_into_magic(t_l_comp *b_phong, t_intersect *ans);
void				calculate_multi_color(t_intersect *ans,t_l_comp *lmod,
							t_light *l, t_scene *scene);
void				calc_spec_part(t_intersect *ans,t_l_comp *lmod,
							t_light *l);
int					blinn_phong(t_intersect *ans, t_scene *scene);
int					col_to_int(t_vector *coeffs, float to_cam);
#endif