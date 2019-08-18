/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 11:21:01 by dmolyboh          #+#    #+#             */
/*   Updated: 2018/11/15 04:55:23 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*c;
	size_t	i;

	i = 0;
	c = ft_memalloc(size + 1);
	if (c == NULL)
		return (NULL);
	while (i <= size)
	{
		c[i] = '\0';
		i++;
	}
	return (c);
}
