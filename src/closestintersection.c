/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closestintersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanderer <wanderer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 00:23:56 by wanderer          #+#    #+#             */
/*   Updated: 2019/08/15 19:04:16 by wanderer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

static void			tnx_norma(double *clst_t, t_object **close_obj,
t_object **sph, t_object **sph_head)
{
	*sph_head = *sph;
	*close_obj = NULL;
	*clst_t = CODE_ERROR;
}

static t_point_d	dop_clse_inter(t_point_d camera_pos, t_point_d direction,
t_object *sph_head)
{
	t_point_d	intersect;

	if (sph_head->name && ft_strstr(sph_head->name, "cylinder"))
		intersect = intesct_cylin(camera_pos, direction, sph_head);
	else if (ft_strstr(sph_head->name, "cone"))
		intersect = intesct_cone(camera_pos, direction, sph_head);
	else if (ft_strstr(sph_head->name, "plane"))
		intersect = intesct_plane(camera_pos, direction, sph_head);
	else
		intersect = intesct_sph(camera_pos, direction, sph_head);
	return (intersect);
}

t_object			*clsettrsctn(t_point_d camera_pos, t_point_d direction,
t_object *sph, t_tp_mx t)
{
	double		clst_t;
	t_point_d	inters;
	t_object	*close_obj;
	t_object	*sph_head;

	tnx_norma(&clst_t, &close_obj, &sph, &sph_head);
	while (sph_head)
	{
		inters = dop_clse_inter(camera_pos, direction, sph_head);
		if (inters.x < clst_t && t.t_min < inters.x && inters.x < t.t_max)
		{
			clst_t = inters.x;
			close_obj = sph_head;
		}
		if (inters.y < clst_t && t.t_min < inters.y && inters.y < t.t_max)
		{
			clst_t = inters.y;
			close_obj = sph_head;
		}
		sph_head = sph_head->next;
	}
	if (close_obj == NULL)
		return (NULL);
	close_obj->clst_t = clst_t;
	return (close_obj);
}
