/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 09:07:26 by ffarah            #+#    #+#             */
/*   Updated: 2021/03/16 13:23:19 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTS_H
# define LIGHTS_H

typedef struct			s_light_complex
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
}						t_light_complex;

t_vector			color_multiply(t_vector *v1, t_vector *v2, double k);
int					shadows(t_object *objs, t_ray *ray, float min_t);
float				return_max_positive(float c);
void				turn_into_magic(t_light_complex *b_phong, t_intersect *ans);
void				light_complex_init(t_intersect *ans, t_scene *scene, t_light_complex *b_phong);
void				light_construction(t_light_complex *b_phong, t_light *l, t_intersect *ans);
void				specular_highlight(t_light_complex *b_phong, t_intersect *ans);
int					blinn_phong(t_intersect *ans, t_scene *scene);
int					col_to_int(t_vector *coeffs, float to_cam);
#endif