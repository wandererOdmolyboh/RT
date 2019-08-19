/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RT.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 13:59:25 by wanderer          #+#    #+#             */
/*   Updated: 2019/08/19 10:55:01 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV_H
# define RTV_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "SDL2/SDL.h"
// # include "SDL2/SDL_image.h"
# include "SDL2_image/SDL_image.h"

# include "../parson/parson.h"
# include "../libft/libft.h"

# define WIDTH 700
# define HEIGH 700
# define TRUE 1
# define FALSE 0
# define BUFF_SIZE 80
# define CODE_ERROR 9223372036854775807.0
# define BACKGROUND_COLOR 0
# define ELPS 0.001
# define PI 0.17453292519
/*
**16777215 WHITE
*/

typedef struct s_point_d		t_point_d;
typedef struct s_object			t_object;
typedef struct s_light			t_light;
typedef struct s_sdl			t_sdl;
typedef struct s_img			t_img;
typedef struct s_rtv			t_rtv;
typedef struct s_tp_mx			t_tp_mx;
typedef struct s_dcrm			t_dcrm;
typedef struct s_sor_norm		t_norm;
typedef	struct s_lst			t_lst;
typedef	struct s_nr_cam_dir		t_nr_cm_dr;
typedef struct s_ret_obj_s		t_ret_obj_s;
typedef struct s_cam			t_cam;
typedef t_object				*t_creator_list_obj(char *s, char *name);
typedef t_light					*t_creator_list_l(char *s, char *name);
typedef double	t_v				__attribute__((__ext_vector_type__(3)));

struct							s_dcrm
{
	double						r;
	double						k1;
	double						k2;
	double						k3;
	double						dcrm;
};

struct							s_point_d
{
	double						x;
	double						y;
	double						z;
};

struct							s_cam
{
	t_point_d					cam_pos;
	t_point_d					rotate_1;
	t_point_d					rotate_2;
	t_point_d					rotate_3;
};

struct							s_tp_mx
{
	t_point_d					vec_l;
	double						t_max;
	double						t_min;
};

struct							s_sor_norm
{
	t_point_d					normal;
	t_point_d					view;
	t_point_d					point;
	t_point_d					local_color;
	t_tp_mx						lt;
	double						i_lg;
};

struct							s_object
{
	char						*name;
	t_point_d					center;
	t_point_d					v_axis;
	t_point_d					normal;
	t_point_d					n;
	t_point_d					color;
	t_point_d					oc;
	double						r;
	double						k;
	double						clst_t;
	int							specular;
	double						reflective;
	int							ch;
	t_object					*next;
};

struct							s_light
{
	char						*name;
	double						intensity;
	t_point_d					direction;
	t_light						*next;
};

struct							s_sdl
{
	SDL_Window					*win;
	SDL_Renderer				*ren;
	SDL_Texture					*textur;
	SDL_Surface					*surf;
	SDL_Event					event;
};

struct							s_img
{
	int							width;
	int							height;
	int							*pixels;
};

struct							s_rtv
{
	t_object					*object;
	t_light						*light;
	t_cam						cam;
	t_sdl						sdlka;
};

struct							s_lst
{
	int							fd;
	char						*line_ret;
	struct s_lst				*next;
};

struct							s_nr_cam_dir
{
	t_point_d					camera_pos;
	t_point_d					direction;
};

struct							s_ret_obj_s
{
	t_object					*sph;
	char						*s;
};

int								get_next_line(const int fd, char **line);
t_point_d						mulv(double k, t_point_d vec);
t_point_d						add(t_point_d v1, t_point_d v2);
t_point_d						sub(t_point_d v1, t_point_d v2);
double							dot(t_point_d v1, t_point_d v2);
double							lngth(t_point_d vec);
t_point_d						intesct_cone(t_point_d cam, t_point_d dir,
t_object *sph);
t_point_d						intesct_cylin(t_point_d cam, t_point_d dir,
t_object *sph);
t_point_d						intesct_plane(t_point_d cam, t_point_d dir,
t_object *sph);
t_point_d						intesct_sph(t_point_d cam, t_point_d dir,
t_object *sph);
void							create_scene(t_cam cam, t_img *img,
t_object *sph, t_light *light);
int								get_color(int r, int g, int b);
void							aligment_color(t_point_d *t);
int								initial_sdl(t_rtv *rtv, t_img *img);
void							sdl_leaks(t_rtv	*rtv, t_img *img);
void							free_list(t_object *obj);
t_object						*clsettrsctn(t_point_d camera_pos,
t_point_d direction, t_object *sph, t_tp_mx t);
int								traceray_c(t_point_d camera_pos,
t_point_d direction, t_object *sph, t_light *light, double dep);
double							compligh(t_object *sph, t_light *lig,
t_norm norma, int specular);
int								get_next_line(const int fd, char **line);
t_point_d						fidn_norma(t_nr_cm_dr dr, t_object *sph,
t_object *clst_obj);
void							free_list_l(t_light *light);
t_object						*c_ls_con(char *line, char *name);
t_object						*c_ls_cldr(char *line, char *name);
t_object						*c_ls_sph(char *line, char *name);
t_object						*c_ls_pln(char *line, char *name);
t_light							*c_ls_en(char *line, char *name);
t_light							*c_ls_pnt(char *line, char *name);
t_light							*c_ls_dir(char *line, char *name);
t_point_d						find_point(char *line);
double							find_value(char *line);
void							ft_list_remove_if_ob(t_object **begin_list);
void							ft_list_remove_if_l(t_light **begin_list);
int								reader(t_rtv *rtv, char *argv);
int								error_val(char **s);
t_point_d						find_point(char *line);
double							find_value(char *line);
t_light							*cr_lst_l(t_light *light1, char *line,
char *name);
t_object						*init_value_o(char *name);
t_light							*init_value_l(char *name);
t_object						*check_list_obj(t_object *obj, char *s,
char *name, t_creator_list_obj *object);
t_light							*check_list_l(t_light *lg, char *s, char *name,
t_creator_list_l	*light);
double							ft_atof(char *nptr);
int								put_error_us(char *name);
int								put_error(char *name);
t_cam							init_value_c();
t_cam							find_cam(char *s);
t_point_d						mullcam(t_point_d cam, t_point_d rot1,
t_point_d rot2, t_point_d rot3);
t_point_d						rotate(t_point_d cam, double angle_x, double angle_y, double angle_z);

#endif
