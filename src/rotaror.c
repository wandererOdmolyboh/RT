/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotaror.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanderer <wanderer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 16:37:12 by wanderer          #+#    #+#             */
/*   Updated: 2019/08/15 19:41:25 by wanderer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

static t_point_d rotate_z(t_point_d cam, double angle)
{
    
    cam.x = cam.x * cos(angle * PI) - cam.y * sin(angle * PI);
    cam.y = -cam.x * sin(angle * PI) + cam.y * cos(angle * PI);
    return (cam);
}

static t_point_d rotate_y(t_point_d cam, double angle)
{
    cam.x = cam.x * cos(angle * PI) + cam.z * sin(angle * PI);
    cam.z = -cam.x * sin(angle * PI) + cam.z * cos(angle * PI);
   return (cam);
}

static t_point_d rotate_x(t_point_d cam, double angle)
{
    cam.x = cam.y * cos(angle * PI) + cam.z * sin(angle * PI);
    cam.z = -cam.y * sin(angle * PI) + cam.z * cos(angle * PI);
	return (cam);
}

t_point_d rotate(t_point_d cam, double angle_x, double angle_y, double angle_z)
{
    if (angle_x != 0.0)
    {
        cam = rotate_x(cam, angle_x);
    }
    if (angle_y != 0.0)
    {
        cam = rotate_y(cam, angle_y);
    }
    if (angle_z != 0.0)
    {
        cam = rotate_z(cam, angle_z);
    }
    return (cam);
}
