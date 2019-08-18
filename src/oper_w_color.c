/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper_w_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanderer <wanderer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 23:42:09 by wanderer          #+#    #+#             */
/*   Updated: 2019/08/15 19:41:49 by wanderer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

int		get_color(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

void	aligment_color(t_point_d *t)
{
	if (t->x > 255)
		t->x = 255;
	else if (t->x < 0)
		t->x = 0;
	if (t->y > 255)
		t->y = 255;
	else if (t->y < 0)
		t->y = 0;
	if (t->z > 255)
		t->z = 255;
	else if (t->z < 0)
		t->z = 0;
}
