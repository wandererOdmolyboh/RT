/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper_w_vector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanderer <wanderer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 23:12:09 by wanderer          #+#    #+#             */
/*   Updated: 2019/08/15 19:41:39 by wanderer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

t_point_d	mulv(double k, t_point_d vec)
{
	t_point_d ret;

	ret.x = (vec.x * k);
	ret.y = (vec.y * k);
	ret.z = (vec.z * k);
	return (ret);
}

t_point_d	add(t_point_d v1, t_point_d v2)
{
	t_point_d ret;

	ret.x = v1.x + v2.x;
	ret.y = v1.y + v2.y;
	ret.z = v1.z + v2.z;
	return (ret);
}

t_point_d	sub(t_point_d v1, t_point_d v2)
{
	t_point_d point;

	point.x = v1.x - v2.x;
	point.y = v1.y - v2.y;
	point.z = v1.z - v2.z;
	return (point);
}

double		dot(t_point_d v1, t_point_d v2)
{
	double point;

	point = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
	return (point);
}

double		lngth(t_point_d vec)
{
	return (sqrt(dot(vec, vec)));
}
