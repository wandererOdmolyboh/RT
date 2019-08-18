/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanderer <wanderer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 13:59:33 by wanderer          #+#    #+#             */
/*   Updated: 2019/08/16 14:29:40 by wanderer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"


void print_params(t_object *obj)
{
	printf("Name is %s\n", obj->name);
	printf("Center %f %f %f\n", obj->center.x, obj->center.y, obj->center.z);
	if (ft_strcmp(obj->name, "plane"))
		printf("Radius == %f\n", obj->r);
	if (ft_strcmp(obj->name, "sphere"))
		printf("Axis %f %f %f\n", obj->v_axis.x, obj->v_axis.y, obj->v_axis.z);
	printf("RGB %f %f %f\n", obj->color.x, obj->color.y, obj->color.z);
	printf("Specular == %d\n", obj->specular);
	if (ft_strcmp(obj->name, "cone"))
		printf("Angle == %f\n", obj->k);
}


int			error_val(char **s)
{
	if (*s == NULL || (*s)++ == NULL)
		return (-1);
	return (1);
}

void		to_zero_buffer(t_img *img)
{
	int i;
	int size;

	i = -1;
	size = img->height * img->width + 1;
	while (++i < size)
		img->pixels[i] = ((255 << 16) | (255 << 8) | 255);
}

int			leakers(t_rtv *rtv, t_img *img, int argc, char *name)
{
	if (argc < 2)
		return (put_error_us(name));
	sdl_leaks(rtv, img);
	free_list(rtv->object);
	free_list_l(rtv->light);
	return (0);
}

void Update_ecran(t_rtv		*rtv, t_img		*img)
{
	SDL_UpdateTexture(rtv->sdlka.textur, NULL, img->pixels, WIDTH * 4);
	SDL_RenderCopy(rtv->sdlka.ren, rtv->sdlka.textur, NULL, NULL);
	SDL_RenderPresent(rtv->sdlka.ren);
}

int			main(int argc, char **argv)
{
	t_rtv		rtv;
	t_img		img;
	

	if (argc < 2 || initial_sdl(&rtv, &img) == -1)
		return (leakers(&rtv, &img, argc, argv[0]));
	rtv.cam = init_value_c();
	rtv.sdlka.surf = SDL_GetWindowSurface(rtv.sdlka.win);
	reader(&rtv, argv[1]);
	create_scene(rtv.cam, &img, rtv.object, rtv.light);
	while (1)
	{
		Update_ecran(&rtv, &img);
		if (SDL_PollEvent(&rtv.sdlka.event) && (rtv.sdlka.event.type
		== SDL_QUIT || rtv.sdlka.event.key.keysym.sym == SDLK_ESCAPE))
		{
			printf("A\n");
			break ;
		}
		if (rtv.sdlka.event.key.keysym.sym == SDLK_c)
		{

			to_zero_buffer(&img);
		}
		if (rtv.sdlka.event.key.keysym.sym == SDLK_SPACE)
		{
			rtv.sdlka.surf->pixels = img.pixels;
			IMG_SavePNG(rtv.sdlka.surf, "t.png");
		}
		if (rtv.sdlka.event.key.keysym.sym == SDLK_v)
		{
			// Сделать чтообы сработало 1 раз
			int i = 0;
			double r,g,b;
			int tmp;
			while (HEIGH * WIDTH > i)
			{
				tmp = img.pixels[i];
				r = (((tmp >> 16) & 0xFF) * 0.393) + (((tmp >> 8) & 0xFF) *0.769) + ((tmp & 0xFF) * 0.189);
				g = (((tmp >> 16) & 0xFF) * 0.349) + (((tmp >> 8) & 0xFF) *0.686) + ((tmp & 0xFF) * 0.168);
				b = (((tmp >> 16) & 0xFF) * 0.272) + (((tmp >> 8) & 0xFF) *0.534) + ((tmp & 0xFF) * 0.131);
				img.pixels[i] = get_color((int)r, (int)g, (int)b);
				i++;
			}
			printf("Aaaa %d 	%d\n", HEIGH * WIDTH, i);
		}
		
		rtv.sdlka.event.key.keysym.sym = 0;
	}
	return (leakers(&rtv, &img, 2, NULL));
}