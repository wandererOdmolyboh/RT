/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list_obj.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanderer <wanderer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 00:53:47 by wanderer          #+#    #+#             */
/*   Updated: 2019/08/15 19:04:32 by wanderer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

t_object	*dop(t_object *obj, char *s)
{
	obj->color = find_point(s);
	if (s == NULL || (s++) == NULL)
		return (obj);
	s = ft_strchr(s, ':');
	if (s == NULL || (s++) == NULL)
		return (obj);
	s = ft_strchr(s, ':');
	obj->specular = find_value(s);
	if (s == NULL || (s++) == NULL)
		return (obj);
	s = ft_strchr(s, ':');
	obj->k = find_value(s);
	return (obj);
}

t_object	*c_ls_con(char *line, char *name)
{
	char		*s;
	t_object	*obj;

	s = line;
	obj = init_value_o(name);
	s = ft_strchr(line, ':');
	obj->center = find_point(s);
	if (s == NULL || (s++) == NULL)
		return (obj);
	s = ft_strchr(s, ':');
	obj->r = find_value(s);
	if (s == NULL || (s++) == NULL)
		return (obj);
	s = ft_strchr(s, ':');
	obj->v_axis = find_point(s);
	obj->n = mulv(1.0 / lngth(obj->v_axis), obj->v_axis);
	if (error_val(&s) == -1 && (s = ft_strchr(s, ':')))
		return (obj);
	return (dop(obj, s));
}

t_object	*c_ls_cldr(char *line, char *name)
{
	char		*s;
	t_object	*obj;

	s = line;
	obj = init_value_o(name);
	s = ft_strchr(line, ':');
	obj->center = find_point(s);
	s = ft_strchr(s, ':');
	if (s == NULL || (s++) == NULL)
		return (obj);
	obj->r = find_value(s);
	s = ft_strchr(s, ':');
	if (s == NULL || (s++) == NULL)
		return (obj);
	obj->v_axis = find_point(s);
	obj->n = mulv(1.0 / lngth(obj->v_axis), obj->v_axis);
	s = ft_strchr(s, ':');
	if (s == NULL || (s++) == NULL)
		return (obj);
	obj->color = find_point(s);
	s = ft_strchr(s, ':');
	if (s == NULL || (s++) == NULL)
		return (obj);
	obj->specular = find_value(s);
	return (obj);
}

t_object	*c_ls_sph(char *line, char *name)
{
	char		*s;
	t_object	*obj;

	s = line;
	obj = init_value_o(name);
	s = ft_strchr(line, ':');
	obj->center = find_point(s);
	if (s == NULL || (s++) == NULL)
		return (obj);
	obj->r = find_value(s);
	s = ft_strchr(s, ':');
	if (s == NULL || (s++) == NULL)
		return (obj);
	obj->color = find_point(s);
	s = ft_strchr(s, ':');
	if (s == NULL || (s++) == NULL)
		return (obj);
	obj->specular = find_value(s);
	return (obj);
}

t_object	*c_ls_pln(char *line, char *name)
{
	char		*s;
	t_object	*obj;

	s = line;
	obj = init_value_o(name);
	obj->r = 5;
	s = ft_strchr(line, ':');
	obj->center = find_point(s);
	if (error_val(&s) == -1)
		return (obj);
	s = ft_strchr(s, ':');
	obj->v_axis = find_point(s);
	obj->n = mulv(1.0 / lngth(obj->v_axis), obj->v_axis);
	if (error_val(&s) == -1)
		return (obj);
	s = ft_strchr(s, ':');
	obj->color = find_point(s);
	if (error_val(&s) == -1)
		return (obj);
	s = ft_strchr(s, ':');
	obj->specular = find_value(s);
	if (error_val(&s) == -1)
		return (obj);
	return (obj);
}
