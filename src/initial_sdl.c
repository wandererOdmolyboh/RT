/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_sdl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 23:45:44 by wanderer          #+#    #+#             */
/*   Updated: 2019/08/19 11:53:45 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

static t_img	create_image(int width, int height)
{
	t_img	img;

	img.width = width;
	img.height = height;
	img.pixels = NULL;
	if ((img.pixels = (int *)malloc(sizeof(int) * (img.width * img.height)))
	== NULL)
		SDL_Log("Memory allocation fault");
	return (img);
}

static int		dop_initial(t_rtv *rtv)
{
	rtv->sdlka.ren = SDL_CreateRenderer(rtv->sdlka.win, -1,
	SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (rtv->sdlka.ren == NULL)
	{
		SDL_Log("SDL_CreateRenderer Error: %s\n", SDL_GetError());
		sdl_leaks(rtv, NULL);
		return (-1);
	}
	if ((rtv->sdlka.textur = SDL_CreateTexture(rtv->sdlka.ren,
	SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
	WIDTH, HEIGH)) == NULL)
	{
		SDL_Log("SDL_CreateTexture Error: %s\n", SDL_GetError());
		sdl_leaks(rtv, NULL);
		return (-1);
	}
	return (0);
}

int				initial_sdl(t_rtv *rtv, t_img *img)
{
	rtv->object = NULL;
	rtv->light = NULL;
	*img = create_image(WIDTH, HEIGH);
	if ((img->pixels) == NULL)
		return (-1);
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		sdl_leaks(rtv, NULL);
		return (-1);
	}
	rtv->sdlka.win = SDL_CreateWindow("RTV1", 100, 100,
	WIDTH, HEIGH, SDL_WINDOW_SHOWN);
	if (rtv->sdlka.win == NULL)
	{
		SDL_Log("Could not create window: %s\n", SDL_GetError());
		sdl_leaks(rtv, NULL);
		return (-1);
	}
	return (dop_initial(rtv));
}

t_object		*init_value_o(char *name)
{
	t_object	*obj;

	if ((obj = (t_object *)malloc(sizeof(t_object))) == NULL)
		return (NULL);
	obj->name = name;
	obj->center.x = 0.0;
	obj->center.y = 0.0;
	obj->center.z = 0.0;
	obj->color.x = 0.0;
	obj->color.y = 0.0;
	obj->color.z = 0.0;
	obj->v_axis.x = 0.0;
	obj->v_axis.y = 0.0;
	obj->v_axis.z = 0.0;
	obj->n.x = 0.0;
	obj->n.y = 0.0;
	obj->n.z = 0.0;
	obj->n = mulv(1.0 / lngth(obj->v_axis), obj->v_axis);
	obj->r = 0.0;
	obj->k = 0.4;
	obj->specular = 0.0;
	obj->reflective = 0;
	obj->next = NULL;
	return (obj);
}

t_light			*init_value_l(char *name)
{
	t_light		*light;

	light = NULL;
	if ((light = (t_light *)malloc(sizeof(t_light))) == NULL)
		return (NULL);
	light->name = name;
	light->direction.x = 0.0;
	light->direction.y = 0.0;
	light->direction.z = 0.0;
	light->intensity = 0.0;
	light->next = NULL;
	return (light);
}
