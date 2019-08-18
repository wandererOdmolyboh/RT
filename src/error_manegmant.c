/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manegmant.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanderer <wanderer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 09:49:43 by dmolyboh          #+#    #+#             */
/*   Updated: 2019/08/15 19:42:13 by wanderer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

int		put_error_us(char *name)
{
	ft_putstr("Usage: ");
	if (name != NULL)
		ft_putstr(name);
	else
		ft_putstr(" RTv1");
	ft_putstr(" file_name\n");
	return (-1);
}

int		put_error(char *name)
{
	ft_putstr(name);
	ft_putstr("\tError\n");
	return (-1);
}
