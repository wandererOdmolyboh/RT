/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanderer <wanderer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 01:26:42 by dmolyboh          #+#    #+#             */
/*   Updated: 2019/08/15 19:41:53 by wanderer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

t_point_d		fidn_norma(t_nr_cm_dr dr, t_object *sph, t_object *ct_ob)
{
	t_norm		nr;
	t_point_d	oc;
	t_point_d	n;
	double		m;

	nr.point = add(dr.camera_pos, mulv(ct_ob->clst_t, dr.direction));
	oc = sub(dr.camera_pos, sph->center);
	if (ft_strstr(ct_ob->name, "cylinder"))
	{
		m = dot(dr.direction, ct_ob->n) * ct_ob->clst_t + dot(oc, ct_ob->n);
		nr.normal = sub(sub(nr.point, ct_ob->center), mulv(m, ct_ob->n));
	}
	else if (ft_strstr(ct_ob->name, "conus"))
	{
		m = (dot(dr.direction, ct_ob->n) * ct_ob->clst_t + dot(oc, ct_ob->n));
		nr.normal = sub(sub(nr.point, ct_ob->center), mulv(m, ct_ob->n));
	}
	else if (ft_strstr(ct_ob->name, "plane"))
	{
		n = ct_ob->n;
		nr.normal = n;
	}
	else
		nr.normal = sub(nr.point, ct_ob->center);
	return (nr.normal);
}
