/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanderer <wanderer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 23:58:18 by wanderer          #+#    #+#             */
/*   Updated: 2019/08/15 19:41:58 by wanderer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

void	sdl_leaks(t_rtv *rtv, t_img *img)
{
	if (rtv->sdlka.textur)
		SDL_DestroyTexture(rtv->sdlka.textur);
	if (rtv->sdlka.ren)
		SDL_DestroyRenderer(rtv->sdlka.ren);
	if (rtv->sdlka.win)
		SDL_DestroyWindow(rtv->sdlka.win);
	if (img->pixels)
		free(img->pixels);
}

void	free_list(t_object *obj)
{
	t_object	*leaks;

	while (obj != NULL)
	{
		leaks = obj;
		obj = obj->next;
		free(leaks);
	}
	leaks = NULL;
	obj = NULL;
}

void	free_list_l(t_light *light)
{
	t_light	*leaks;

	leaks = light;
	while (leaks)
	{
		free(leaks);
		leaks = leaks->next;
	}
	leaks = NULL;
	light = NULL;
}

void	ft_list_remove_if_ob(t_object **begin_list)
{
	t_object	*tmp;
	t_object	*new_begin_list;

	while (*begin_list && (*begin_list)->r <= 0 &&
	(!ft_strcmp((*begin_list)->name, "plane")))
	{
		tmp = *begin_list;
		*begin_list = (*begin_list)->next;
		write(1, "radius < 0 is not good\n", 24);
		free(tmp);
	}
	new_begin_list = *begin_list;
	while (new_begin_list && new_begin_list->next)
	{
		if (new_begin_list->next->r <= 0
		&& (!ft_strcmp((*begin_list)->name, "plane")))
		{
			tmp = new_begin_list->next;
			new_begin_list->next = tmp->next;
			free(tmp);
		}
		if (new_begin_list->next)
			new_begin_list = new_begin_list->next;
	}
}

void	ft_list_remove_if_l(t_light **begin_list)
{
	t_light	*tmp;
	t_light	*new_begin_list;

	while (*begin_list && (*begin_list)->intensity <= 0)
	{
		tmp = *begin_list;
		*begin_list = (*begin_list)->next;
		free(tmp);
	}
	new_begin_list = *begin_list;
	while (new_begin_list && new_begin_list->next)
	{
		if (new_begin_list->next->intensity <= 0)
		{
			tmp = new_begin_list->next;
			new_begin_list->next = tmp->next;
			free(tmp);
		}
		if (new_begin_list->next)
			new_begin_list = new_begin_list->next;
	}
}
