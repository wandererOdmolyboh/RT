/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computelighting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanderer <wanderer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 00:23:59 by wanderer          #+#    #+#             */
/*   Updated: 2019/08/15 19:04:13 by wanderer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

static double	dop_com_ligh(t_light *lg, t_point_d vec_l, t_norm norma,
int specular)
{
	double		intensity;
	double		n_dot_l;
	double		r_dot_v;
	t_point_d	vec_r;

	intensity = 0;
	n_dot_l = dot(norma.normal, vec_l);
	if (n_dot_l > 0.0)
		intensity += lg->intensity * n_dot_l /
		(lngth(norma.normal) * lngth(vec_l));
	if (specular > 0)
	{
		vec_r = sub(mulv(2.0 * dot(norma.normal, vec_l), norma.normal)
		, vec_l);
		r_dot_v = dot(vec_r, norma.view);
		if (r_dot_v > 0.0)
		{
			intensity += lg->intensity * pow(r_dot_v / (lngth(vec_r)
			* lngth(norma.view)), specular);
		}
	}
	return (intensity);
}

t_tp_mx			type_ligh(t_point_d point, t_light *lg)
{
	t_tp_mx		lt;

	if (ft_strstr(lg->name, "POINT"))
	{
		lt.vec_l = sub(lg->direction, point);
		lt.t_max = 1.0;
	}
	else
	{
		lt.vec_l = lg->direction;
		lt.t_max = CODE_ERROR;
	}
	lt.t_min = ELPS;
	return (lt);
}

double			compligh(t_object *sph, t_light *lig, t_norm norma,
int specular)
{
	double		intensity;
	t_light		*lg;
	t_tp_mx		lt;
	t_object	*blocker;

	intensity = 0.0;
	lg = lig;
	while (lg)
	{
		if (ft_strstr(lg->name, "AMBIENT"))
			intensity += lg->intensity;
		else
		{
			lt = type_ligh(norma.point, lg);
			blocker = clsettrsctn(norma.point, lt.vec_l, sph, lt);
			if (blocker)
			{
				lg = lg->next;
				continue ;
			}
			intensity += dop_com_ligh(lg, lt.vec_l, norma, specular);
		}
		lg = lg->next;
	}
	return (intensity);
}
