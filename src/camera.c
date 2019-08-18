/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanderer <wanderer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 10:05:06 by dmolyboh          #+#    #+#             */
/*   Updated: 2019/08/15 19:04:09 by wanderer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

t_cam			init_value_c(void)
{
	t_cam		cam;

	cam.cam_pos.x = 9.0;
	cam.cam_pos.y = 0.0;
	cam.cam_pos.z = -5.0;
	cam.rotate_1.x = 0.7071;
	cam.rotate_1.y = 0.0;
	cam.rotate_1.z = -0.7071;
	cam.rotate_2.x = 0.0;
	cam.rotate_2.y = 1.0;
	cam.rotate_2.z = 0.0;
	cam.rotate_3.x = 0.7071;
	cam.rotate_3.y = 0.0;
	cam.rotate_3.z = 0.7071;
	return (cam);
}


t_cam			find_cam(char *line)
{
	char		*s;
	t_cam		cam;

	cam = init_value_c();
	s = ft_strchr(line, ':');
	cam.cam_pos = find_point(s);
	if (error_val(&s) == -1 && (s = ft_strchr(s, ':')))
		return (cam);
	if ((s = ft_strchr(s, ':')) == NULL)
		return (cam);
	cam.rotate_1 = find_point(s);
	if (error_val(&s) == -1 && (s = ft_strchr(s, ':')))
		return (cam);
	s = ft_strchr(s, ':');
	cam.rotate_2 = find_point(s);
	if (error_val(&s) == -1 && (s = ft_strchr(s, ':')))
		return (cam);
	s = ft_strchr(s, ':');
	cam.rotate_2 = find_point(s);
	if (error_val(&s) == -1 && (s = ft_strchr(s, ':')))
		return (cam);
	return (cam);
}

t_point_d		mullcam(t_point_d cam, t_point_d rot1,
t_point_d rot2, t_point_d rot3)
{
	t_point_d	rez;

	rez.x = cam.x * rot1.x;
	rez.x += cam.y * rot1.y;
	rez.x += cam.z * rot1.z;
	rez.y = cam.x * rot2.x;
	rez.y += cam.y * rot2.y;
	rez.y += cam.z * rot2.z;
	rez.z = cam.x * rot3.x;
	rez.z += cam.y * rot3.y;
	rez.z += cam.z * rot3.z;
	return (rez);
}


// t_point_d	MultiplyMV(t_cam mat,	t_point_d	vec)
// {
// 	t_point_d rez;

// 	rez.x = vec.x * mat.rotate_1.x
// 	+ vec.y * mat.rotate_1.y
// 	+ vec.z * mat.rotate_1.z;
// 	rez.y = vec.x * mat.rotate_2.x
// 	+ vec.y * mat.rotate_2.y
// 	+ vec.z * mat.rotate_2.z;
// 	rez.z = vec.x * mat.rotate_3.x
// 	+ vec.y * mat.rotate_3.y
// 	+ vec.z * mat.rotate_3.z;
// 	return (rez);
// }