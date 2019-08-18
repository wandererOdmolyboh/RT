/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanderer <wanderer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 14:23:31 by wanderer          #+#    #+#             */
/*   Updated: 2019/08/15 19:41:36 by wanderer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

t_object	*check_list_obj(t_object *obj, char *s,
char *name, t_creator_list_obj *object)
{
	t_object	*rez;
	t_object	*head;

	if (obj == NULL)
		obj = object(s, name);
	else
	{
		head = obj;
		while (head->next != NULL)
			head = head->next;
		rez = object(s, name);
		head->next = rez;
	}
	return (obj);
}

t_light		*check_list_l(t_light *lg, char *s,
char *name, t_creator_list_l *light)
{
	t_light		*rez;
	t_light		*head;

	if (lg == NULL)
		lg = light(s, name);
	else
	{
		head = lg;
		while (head->next != NULL)
			head = head->next;
		rez = light(s, name);
		head->next = rez;
	}
	return (lg);
}
