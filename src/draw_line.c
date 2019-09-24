/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 19:04:41 by mhonchar          #+#    #+#             */
/*   Updated: 2019/09/12 20:09:59 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ft_pp_img(Uint32 *pixels, int x, int y, Uint32 color)
{
	if ((x >= 0 && x < CW) && (y >= 0 && y < CH))
		pixels[CW * y + x] = color;
}
