/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_scene.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:36:20 by alex              #+#    #+#             */
/*   Updated: 2021/02/06 17:36:33 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ADD_SCENE_H
# define ADD_SCENE_H
void		add_light(t_light **lights, t_light *light);
void		add_canvas(t_scene *scene, t_canvas *new);
void		add_camera(t_scene *scene, t_camera *cam);

#endif