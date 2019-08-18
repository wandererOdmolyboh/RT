/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_objct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanderer <wanderer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 23:10:45 by wanderer          #+#    #+#             */
/*   Updated: 2019/08/15 19:42:02 by wanderer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

t_point_d	intesct_cone(t_point_d cam, t_point_d dir, t_object *obj)
{
	t_point_d	intersect;
	t_point_d	oc;
	t_dcrm		dis;

	dis.r = obj->r;
	oc = sub(cam, obj->center);
	dis.k1 = dot(dir, dir) - (1 + obj->k * obj->k) * pow((dot(dir, obj->n)),
	2.0);
	dis.k2 = 2.0 * ((dot(oc, dir) - (1 + obj->k * obj->k) * (dot(oc, obj->n)
	* dot(dir, obj->n))));
	dis.k3 = dot(oc, oc) - (1 + obj->k * obj->k) * pow(dot(oc, obj->n), 2.0);
	dis.dcrm = dis.k2 * dis.k2 - 4 * dis.k1 * dis.k3;
	if (dis.dcrm < 0.0)
	{
		intersect.x = CODE_ERROR;
		intersect.y = CODE_ERROR;
		intersect.z = CODE_ERROR;
		return (intersect);
	}
	intersect.x = (-dis.k2 + sqrt(dis.dcrm)) / (2.0 * dis.k1);
	intersect.y = (-dis.k2 - sqrt(dis.dcrm)) / (2.0 * dis.k1);
	intersect.z = 0.0;
	return (intersect);
}

t_point_d	intesct_cylin(t_point_d cam, t_point_d dir, t_object *obj)
{
	t_point_d	intersect;
	t_point_d	oc;
	t_dcrm		dis;

	oc = sub(cam, obj->center);
	dis.r = obj->r;
	dis.k1 = dot(dir, dir) - pow(dot(dir, obj->n), 2.0);
	dis.k2 = 2.0 * (dot(oc, dir) - (dot(oc, obj->n) * dot(dir, obj->n)));
	dis.k3 = dot(oc, oc) - pow(dot(oc, obj->n), 2.0) - dis.r * dis.r;
	dis.dcrm = dis.k2 * dis.k2 - 4 * dis.k1 * dis.k3;
	if (dis.dcrm < 0.0)
	{
		intersect.x = CODE_ERROR;
		intersect.y = CODE_ERROR;
		intersect.z = CODE_ERROR;
		return (intersect);
	}
	intersect.x = (-dis.k2 + sqrt(dis.dcrm)) / (2.0 * dis.k1);
	intersect.y = (-dis.k2 - sqrt(dis.dcrm)) / (2.0 * dis.k1);
	intersect.z = 0.0;
	return (intersect);
}

t_point_d	intesct_plane(t_point_d cam, t_point_d dir, t_object *obj)
{
	t_point_d intersect;
	t_point_d oc;
	t_point_d n;

	n = obj->n;
	if (dot(dir, obj->n) < 0.0001)
	{
		n = mulv(-1, obj->n);
		if (dot(dir, n) < 0.0001)
		{
			intersect.x = CODE_ERROR;
			intersect.y = CODE_ERROR;
			intersect.z = CODE_ERROR;
			return (intersect);
		}
	}
	oc = sub(cam, obj->center);
	intersect.x = dot(mulv(-1, oc), n) / dot(dir, n);
	intersect.y = intersect.x;
	return (intersect);
}

t_point_d	intesct_sph(t_point_d cam, t_point_d dir, t_object *sph)
{
	t_point_d	intersect;
	t_point_d	oc;
	t_dcrm		dis;

	oc = sub(cam, sph->center);
	dis.r = sph->r;
	dis.k1 = dot(dir, dir);
	dis.k2 = 2.0 * dot(oc, dir);
	dis.k3 = dot(oc, oc) - dis.r * dis.r;
	dis.dcrm = dis.k2 * dis.k2 - 4 * dis.k1 * dis.k3;
	if (dis.dcrm < 0.0)
	{
		intersect.x = CODE_ERROR;
		intersect.y = CODE_ERROR;
		intersect.z = CODE_ERROR;
		return (intersect);
	}
	intersect.x = (-dis.k2 + sqrt(dis.dcrm)) / (2.0 * dis.k1);
	intersect.y = (-dis.k2 - sqrt(dis.dcrm)) / (2.0 * dis.k1);
	intersect.z = 0.0;
	return (intersect);
}
