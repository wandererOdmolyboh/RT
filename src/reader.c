/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanderer <wanderer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 04:46:25 by dmolyboh          #+#    #+#             */
/*   Updated: 2019/08/15 19:41:28 by wanderer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

void		ft_list_remove_if_obk(t_object **begin_list)
{
	t_object	*tmp;
	t_object	*new_begin_list;

	while (*begin_list && ((*begin_list)->k <= 0 || (*begin_list)->k >= 1) &&
	(ft_strcmp((*begin_list)->name, "cone") == 0))
	{
		tmp = *begin_list;
		*begin_list = (*begin_list)->next;
		free(tmp);
	}
	new_begin_list = *begin_list;
	while (new_begin_list && new_begin_list->next)
	{
		if ((new_begin_list->next->k <= 0 || new_begin_list->next->k >= 1)
		&& (ft_strcmp((*begin_list)->name, "cone") == 0))
		{
			tmp = new_begin_list->next;
			new_begin_list->next = tmp->next;
			free(tmp);
		}
		if (new_begin_list->next)
			new_begin_list = new_begin_list->next;
	}
}

t_point_d	find_point(char *line)
{
	t_point_d	point;
	char		*s;

	point.x = 0;
	point.y = 0;
	point.z = 0;
	s = ft_strchr(line, ':');
	if (error_val(&s) == -1)
		return (point);
	point.x = ft_atof(s);
	s = ft_strchr(s, ',');
	if (error_val(&s) == -1)
		return (point);
	point.y = ft_atof(s);
	s = ft_strchr(s, ',');
	if (error_val(&s) == -1)
		return (point);
	point.z = ft_atof(s);
	return (point);
}

double		find_value(char *line)
{
	double		value;
	char		*s;

	s = ft_strchr(line, ':');
	if (error_val(&s) == -1)
		return (0);
	value = ft_atof(s);
	return (value);
}

static int	lister(t_object *object, t_light *light, int fd)
{
	ft_list_remove_if_ob(&object);
	ft_list_remove_if_l(&light);
	ft_list_remove_if_obk(&object);
	close(fd);
	return (0);
}

int			reader(t_rtv *rtv, char *argv)
{
	char		*s;
	int			fd;

	fd = open(argv, O_RDONLY);
	while (get_next_line(fd, &s) > 0)
	{
		if (ft_strstr(s, "sphere"))
			rtv->object = check_list_obj(rtv->object, s, "sphere", c_ls_sph);
		else if (ft_strstr(s, "cylinder"))
			rtv->object = check_list_obj(rtv->object, s, "cylinder", c_ls_cldr);
		else if (ft_strstr(s, "cone"))
			rtv->object = check_list_obj(rtv->object, s, "cone", c_ls_con);
		else if (ft_strstr(s, "plane"))
			rtv->object = check_list_obj(rtv->object, s, "plane", c_ls_pln);
		else if (ft_strstr(s, "AMBIENT"))
			rtv->light = check_list_l(rtv->light, s, "AMBIENT", c_ls_en);
		else if (ft_strstr(s, "POINT"))
			rtv->light = check_list_l(rtv->light, s, "POINT", c_ls_pnt);
		else if (ft_strstr(s, "DIRECTIONAL"))
			rtv->light = check_list_l(rtv->light, s, "DIRECTIONAL", c_ls_dir);
		else if (ft_strstr(s, "cam"))
			rtv->cam = find_cam(s);
		free(s);
	}
	return (lister(rtv->object, rtv->light, fd));
}
