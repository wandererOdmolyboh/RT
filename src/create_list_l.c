/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list_l.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanderer <wanderer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 00:53:42 by wanderer          #+#    #+#             */
/*   Updated: 2019/08/15 19:04:28 by wanderer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

t_light	*c_ls_en(char *line, char *name)
{
	char		*s;
	t_light		*light;

	s = line;
	light = init_value_l(name);
	s = ft_strchr(line, ':');
	light->intensity = find_value(s);
	if (error_val(&s) == -1)
		return (light);
	return (light);
}

t_light	*c_ls_pnt(char *line, char *name)
{
	char		*s;
	t_light		*light;

	s = line;
	light = init_value_l(name);
	s = ft_strchr(line, ':');
	light->intensity = find_value(s);
	if (error_val(&s) == -1)
		return (light);
	light->direction = find_point(s);
	if (error_val(&s) == -1)
		return (light);
	return (light);
}

t_light	*c_ls_dir(char *line, char *name)
{
	char		*s;
	t_light		*light;

	s = line;
	light = init_value_l(name);
	s = ft_strchr(line, ':');
	light->intensity = find_value(s);
	if (error_val(&s) == -1)
		return (light);
	light->direction = find_point(s);
	if (error_val(&s) == -1)
		return (light);
	return (light);
}
