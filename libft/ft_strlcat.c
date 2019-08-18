/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 09:39:04 by dmolyboh          #+#    #+#             */
/*   Updated: 2018/11/19 02:12:59 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, char *src, size_t n)
{
	size_t	dstl;
	size_t	srcl;
	size_t	i;

	i = 0;
	dstl = ft_strlen(dest);
	srcl = ft_strlen(src);
	if (n <= dstl)
		return (srcl + n);
	while (dest[i] != '\0' && i < n)
		i++;
	while (*src && i < (n - 1))
	{
		dest[i] = *src;
		i++;
		src++;
	}
	dest[i] = '\0';
	return (dstl + srcl);
}
