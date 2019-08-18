/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanderer <wanderer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 01:27:27 by dmolyboh          #+#    #+#             */
/*   Updated: 2019/08/16 13:54:12 by wanderer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"


t_point_d ReflectRay (t_point_d v1, t_point_d v2)
{
  return (sub(mulv(2*dot(v1, v2), v2), v1));
} 

int	traceray_c(t_point_d camera_pos, t_point_d direction,
t_object *sph, t_light *light, double dep)
{
	t_object	*clst_obj;
	t_object	*head;
	t_light		*ligh;
	t_norm		norma;
	t_nr_cm_dr	cam;

	cam.camera_pos = camera_pos;
	cam.direction = direction;
	norma.lt.t_max = CODE_ERROR;
	norma.lt.t_min = ELPS;
	ligh = light;
	clst_obj = clsettrsctn(camera_pos, direction, sph, norma.lt);
	if (clst_obj == NULL)
		return (BACKGROUND_COLOR);
	norma.point = add(camera_pos, mulv(clst_obj->clst_t, direction));
	norma.normal = fidn_norma(cam, sph, clst_obj);
	norma.normal = mulv(1.0 / lngth(norma.normal), norma.normal);
	norma.view = mulv(-1.0, direction);
	head = sph;
	norma.i_lg = compligh(head, ligh, norma, clst_obj->specular);


	norma.local_color.x = ((int)(((clst_obj->color.x)) * norma.i_lg));
	norma.local_color.y = (int)(((clst_obj->color.y)) * norma.i_lg);
	norma.local_color.z = (int)(((clst_obj->color.z)) * norma.i_lg);
	aligment_color(&norma.local_color);

	if (clst_obj->reflective <= 0 || dep <= 0)
	{
		return (get_color((int)norma.local_color.x, (int)norma.local_color.y, (int)norma.local_color.z));
	}
	t_point_d reflected_ray = ReflectRay(norma.view, norma.normal);
	int reflected_color = traceray_c(norma.point, reflected_ray, head, ligh, dep - 1);
	t_point_d helper;
	helper.x = (reflected_color >> 16) & 0xFF;
	helper.y = (reflected_color >> 8) & 0xFF;
	helper.z = reflected_color & 0xFF;

	helper = (add(mulv(1 - clst_obj->reflective, norma.local_color),
		 mulv(clst_obj->reflective, helper)));


	aligment_color(&helper);
	return (get_color((int)helper.x, (int)helper.y, (int)helper.z));
	
	// norma.t.x = ((int)(((clst_obj->color.x)) * norma.i_lg));
	// norma.t.y = (int)(((clst_obj->color.y)) * norma.i_lg);
	// norma.t.z = (int)(((clst_obj->color.z)) * norma.i_lg);
	// return (get_color((int)norma.t.x, (int)norma.t.y, (int)norma.t.z));
}
