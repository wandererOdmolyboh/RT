/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 15:46:40 by dmolyboh          #+#    #+#             */
/*   Updated: 2018/11/06 17:38:01 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dst1;
	const unsigned char	*src1;
	size_t				carta;

	dst1 = dst;
	src1 = src;
	carta = 0;
	if (dst1 < src1)
		while (len > carta)
		{
			dst1[carta] = src1[carta];
			carta++;
		}
	else
		while (len--)
			dst1[len] = src1[len];
	return ((unsigned char *)(dst));
}
