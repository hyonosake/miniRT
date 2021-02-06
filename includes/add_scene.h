/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_scene.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarah <ffarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:36:20 by alex              #+#    #+#             */
/*   Updated: 2021/02/06 20:13:24 by ffarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ADD_SCENE_H
# define ADD_SCENE_H
void		add_canvas(t_scene *scene, t_canvas *new);
void		add_camera(t_scene *scene, t_camera *cam);
void		add_amb_light(t_scene *scene, t_light *amb);
void		add_light(t_scene *scene, t_light *l);
void		add_object(t_scene *scene, t_object *obj);
#endif