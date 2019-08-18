/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanderer <wanderer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 15:35:57 by wanderer          #+#    #+#             */
/*   Updated: 2019/08/15 19:39:34 by wanderer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

// ======================================================================
//  Low-level canvas access. 
// ======================================================================


static void			set_pixel(t_img *img, int x, int y, int color)
{
	int			tmpx;
	int			tmpy;

	tmpx = img->width / 2 + x;
	tmpy = img->height / 2 - y - 1;
	if (tmpx < 0 || tmpx > (int)img->width
	|| tmpy < 0 || tmpy > (int)img->height)
		return ;
	img->pixels[tmpx + tmpy * img->width] = color;
}

static t_point_d	can_view(int x, int y, t_img *img)
{
	t_point_d	d;

	d.x = (double)((double)x * 1.0 / (double)img->width);
	d.y = (double)((double)y * 1.0 / (double)img->height);
	d.z = 1;
	return (d);
}





var PutPixel = function(x, y, color)
{
	x = canvas.width/2 + x;
	y = canvas.height/2 - y - 1;
	if (x < 0 || x >= canvas.width || y < 0 || y >= canvas.height)
	{
		return;
	}
	var offset = 4*x + canvas_pitch*y;
	canvas_buffer.data[offset++] = color[0];
	canvas_buffer.data[offset++] = color[1];
	canvas_buffer.data[offset++] = color[2];
	canvas_buffer.data[offset++] = 255; // Alpha = 255 (full opacity)
}
// Displays the contents of the offscreen buffer into the canvas.
var UpdateCanvas = function()
{
	canvas_context.putImageData(canvas_buffer, 0, 0);
}
// ======================================================================
//  Linear algebra and helpers.
// ======================================================================
// Conceptually, an "infinitesimaly small" real number.
var EPSILON = 0.001;
// Dot product of two 3D vectors.
var DotProduct = function(v1, v2)
{
	return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];  
}
// Length of a 3D vector.
var Length = function(vec)
{
	return Math.sqrt(DotProduct(vec, vec));
}
// Multiplies a scalar and a vector.
var MultiplySV = function(k, vec)
{
	return [k*vec[0], k*vec[1], k*vec[2]];
}
// Multiplies a matrix and a vector.
var MultiplyMV = function(mat, vec)
{
	var result = [0, 0, 0];
	for (var i = 0; i < 3; i++)
	{
		for (var j = 0; j < 3; j++)
		{
			result[i] += vec[j]*mat[i][j];
		}
	}
	return (result);
}
// Computes v1 + v2.
var Add = function(v1, v2)
{
	return ([v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]]);
}
// Computes v1 - v2.
var Subtract = function(v1, v2)
{
	return ([v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2]]);
}
// Clamps a color to the canonical color range.
var Clamp = function(vec)
{
	return [Math.min(255, Math.max(0, vec[0])),
	  Math.min(255, Math.max(0, vec[1])),
	  Math.min(255, Math.max(0, vec[2]))]; 
}
// Computes the reflection of v1 respect to v2.
var ReflectRay = function(v1, v2)
{
	return Subtract(MultiplySV(2*DotProduct(v1, v2), v2), v1);
} 
// ======================================================================
//  A raytracer with diffuse and specular illumination, shadows and reflections,
// arbitrary camera position and orientation.
// ======================================================================
// A Sphere.
var Sphere = function(center, radius, color, specular, reflective)
{
	this.center = center;
	this.radius = radius;
	this.color = color;
	this.specular = specular;
	this.reflective = reflective;
}
// A Light.
var Light = function(ltype, intensity, position)
{
	this.ltype = ltype;
	this.intensity = intensity;
	this.position = position;
}

Light.AMBIENT = 0;
Light.POINT = 1;
Light.DIRECTIONAL = 2;
// Scene setup.
var viewport_size = 1;
var projection_plane_z = 1;
var camera_position = [3, 0, 1];
var camera_rotation = [[0.7071, 0, -0.7071],
			   [     0, 1,       0],
			   [0.7071, 0,  0.7071]];
var background_color = [0, 0, 0];
var spheres = [new Sphere([0, -1, 3], 1, [255, 0, 0], 500, 0.2),
		   new Sphere([2, 0, 4], 1, [0, 0, 255], 500, 0.3),
		   new Sphere([-2, 0, 4], 1, [0, 255, 0], 10, 0.4), 
		   new Sphere([0, -5001, 0], 5000, [255, 255, 0], 1000, 0.5)];
var lights = [
  new Light(Light.AMBIENT, 0.2),
  new Light(Light.POINT, 0.6, [2, 1, 0]),
  new Light(Light.DIRECTIONAL, 0.2, [1, 4, 4])
];
var recursion_depth = 3;
// Converts 2D canvas coordinates to 3D viewport coordinates.
var CanvasToViewport = function(p2d)
{
	return [p2d[0] * viewport_size / canvas.width,
	  p2d[1] * viewport_size / canvas.height,
	  projection_plane_z]; 
}
// Computes the intersection of a ray and a sphere. Returns the values
// of t for the intersections.
var IntersectRaySphere = function(origin, direction, sphere)
{
	var oc = Subtract(origin, sphere.center);
	var k1 = DotProduct(direction, direction);
	var k2 = 2*DotProduct(oc, direction);
	var k3 = DotProduct(oc, oc) - sphere.radius*sphere.radius;
	var discriminant = k2*k2 - 4*k1*k3;
	if (discriminant < 0)
	{
		return [Infinity, Infinity];
	}
	var t1 = (-k2 + Math.sqrt(discriminant)) / (2*k1);
	var t2 = (-k2 - Math.sqrt(discriminant)) / (2*k1);
	return ([t1, t2]);
}

var ComputeLighting = function(point, normal, view, specular)
{
	var intensity = 0;
	var length_n = Length(normal);// Should be 1.0, but just in case...
	var length_v = Length(view);
	for (var i = 0; i < lights.length; i++)
	{
		var light = lights[i];
		if (light.ltype == Light.AMBIENT)
		{
	  		intensity += light.intensity;
		}
		else
		{
			var vec_l, t_max;
			if (light.ltype == Light.POINT)
			{
				vec_l = Subtract(light.position, point);
				t_max = 1.0;
			}
			else
			{  // Light.DIRECTIONAL
				vec_l = light.position;
				t_max = Infinity;
			}
	  // Shadow check.
			var blocker = ClosestIntersection(point, vec_l, EPSILON, t_max);
			if (blocker)
			{
				continue;
			}
	  // Diffuse reflection.
			var n_dot_l = DotProduct(normal, vec_l);
			if (n_dot_l > 0)
			{
				intensity += light.intensity * n_dot_l / (length_n * Length(vec_l));
			}
	  // Specular reflection.
			if (specular != -1)
			{
				var vec_r = ReflectRay(vec_l, normal);
				var r_dot_v = DotProduct(vec_r, view);
				if (r_dot_v > 0)
				{
					intensity += light.intensity *
					Math.pow(r_dot_v / (Length(vec_r) * length_v), specular); 
				}
			}
		}
	}
  return (intensity);
}
// Find the closest intersection between a ray and the spheres in the scene.
var ClosestIntersection = function(origin, direction, min_t, max_t)
{
	var closest_t = Infinity;
	var closest_sphere = null;

	for (var i = 0; i < spheres.length; i++)
	{
		var ts = IntersectRaySphere(origin, direction, spheres[i]);
		if (ts[0] < closest_t && min_t < ts[0] && ts[0] < max_t)
		{
			closest_t = ts[0];
			closest_sphere = spheres[i];
		}
		if (ts[1] < closest_t && min_t < ts[1] && ts[1] < max_t)
		{
			closest_t = ts[1];
			closest_sphere = spheres[i];
		}
	}
	if (closest_sphere)
	{
		return [closest_sphere, closest_t];
	}
	return (NULL);
}
// Traces a ray against the set of spheres in the scene.
var TraceRay = function(origin, direction, min_t, max_t, depth)
{
	var intersection = ClosestIntersection(origin, direction, min_t, max_t);
	if (!intersection)
	{
		return background_color;
	}
	var closest_sphere = intersection[0];
	var closest_t = intersection[1];
	var point = Add(origin, MultiplySV(closest_t, direction));
	var normal = Subtract(point, closest_sphere.center);
	normal = MultiplySV(1.0 / Length(normal), normal);
	var view = MultiplySV(-1, direction);
	var lighting = ComputeLighting(point, normal, view, closest_sphere.specular);
	
	var local_color = MultiplySV(lighting, closest_sphere.color);


	
	if (closest_sphere.reflective <= 0 || depth <= 0)
	{
		return local_color;
	}
	var reflected_ray = ReflectRay(view, normal);
	var reflected_color = TraceRay(point, reflected_ray, EPSILON, Infinity, depth - 1);

	return (Add(MultiplySV(1 - closest_sphere.reflective, local_color),
		 MultiplySV(closest_sphere.reflective, reflected_color)));
}

//
// Main loop.
//

int	traceray_c(t_point_d camera_pos, t_point_d direction,
t_object *sph, t_light *light, double depth)
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


	if (closest_sphere.reflective <= 0 || depth <= 0)
	{
		return local_color;
	}
	var reflected_ray = ReflectRay(view, normal);
	var reflected_color = TraceRay(point, reflected_ray, EPSILON, Infinity, depth - 1);

	return (Add(MultiplySV(1 - closest_sphere.reflective, local_color),
		 MultiplySV(closest_sphere.reflective, reflected_color)));

	return (get_color((int)norma.t.x, (int)norma.t.y, (int)norma.t.z));
}

	// norma.t.x = ((int)(((clst_obj->color.x)) * norma.i_lg));
	// norma.t.y = (int)(((clst_obj->color.y)) * norma.i_lg);
	// norma.t.z = (int)(((clst_obj->color.z)) * norma.i_lg);
	// aligment_color(&norma.t);
void				create_scene(t_cam cam, t_img *img,
t_object *sph, t_light *light)
{
	t_point_d	camera_pos;
	t_point_d	direction;
	int			color;
	int			x;
	int			y;
	double		recursion_depth = 3;

	camera_pos = cam.cam_pos;
	x = -img->width / 2 - 1;
	while (++x < (img->width / 2))
	{
		y = -img->height / 2 - 1;
		while (++y < (img->height / 2))
		{
			direction = can_view(x, y, img);
			// direction = rotate(direction, 0, 0, 0);
			direction = mullcam(direction, cam.rotate_1, cam.rotate_2, cam.rotate_3);
			color = traceray_c(camera_pos, direction, sph, light, recursion_depth);
			set_pixel(img, x, y, color);
		}
	}
}


// for (var x = -canvas.width/2; x < canvas.width/2; x++) {
//   for (var y = -canvas.height/2; y < canvas.height/2; y++) {
// 	var direction = CanvasToViewport([x, y])
// 	direction = MultiplyMV(camera_rotation, direction);
// 	var color = TraceRay(camera_position, direction, 1, Infinity, recursion_depth);
// 	set_pixel(x, y, Clamp(color));
//   }
// }
// UpdateCanvas();

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
		return (0);

	
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
		if (rtv.sdlka.event.key.keysym.sym == SDLK_SPACE)
		{
			rtv.sdlka.surf->pixels = img.pixels;
			IMG_SavePNG(rtv.sdlka.surf, "t.png");
		}
		rtv.sdlka.event.key.keysym.sym = 0;
	}
	return (0);
}