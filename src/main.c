/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 13:59:33 by wanderer          #+#    #+#             */
/*   Updated: 2019/08/19 18:08:17 by dmolyboh         ###   ########.fr       */
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
	// t_v v;
	JSON_Value *shema;
	// JSON_Status nummber;
	// JSON_Value * t;
	shema = json_parse_file(argv[1]);
	// JSON_Status json_validate(const JSON_Value *schema, const JSON_Value *value);
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
			break ; 
		
		rtv.sdlka.event.key.keysym.sym = 0;
	}
	return (leakers(&rtv, &img, 2, NULL));
}
