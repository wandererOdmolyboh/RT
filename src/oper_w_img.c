/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper_w_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanderer <wanderer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 23:37:52 by wanderer          #+#    #+#             */
/*   Updated: 2019/08/16 13:42:05 by wanderer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

static void			set_pixel(t_img *img, int x, int y, int color)
{
	int			tmpx;
	int			tmpy;

	tmpx = img->width / 2 + x;
	tmpy = img->height / 2 - y - 1;
	if (tmpx < 0 || tmpx > (int)img->width
	|| tmpy < 0 || tmpy > (int)img->height)
		return ;
	img->pixels[tmpx + tmpy * img->width] = color;
}

static t_point_d	can_view(int x, int y, t_img *img)
{
	t_point_d	d;

	d.x = (double)((double)x * 1.0 / (double)img->width);
	d.y = (double)((double)y * 1.0 / (double)img->height);
	d.z = 1;
	return (d);
}

void				create_scene(t_cam cam, t_img *img,
t_object *sph, t_light *light)
{
	t_point_d	camera_pos;
	t_point_d	direction;
	int			color;
	int			x;
	int			y;
	double		dep = 40;

	camera_pos = cam.cam_pos;
	x = -img->width / 2 - 1;
	while (++x < (img->width / 2))
	{
		y = -img->height / 2 - 1;
		while (++y < (img->height / 2))
		{
			direction = can_view(x, y, img);
			// direction = rotate(direction, 0, 0, 0);
			direction = mullcam(direction, cam.rotate_1, cam.rotate_2, cam.rotate_3);
			color = traceray_c(camera_pos, direction, sph, light, dep);
			set_pixel(img, x, y, color);
		}
	}
}
