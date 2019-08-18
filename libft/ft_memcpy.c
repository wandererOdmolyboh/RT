/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 10:47:34 by dmolyboh          #+#    #+#             */
/*   Updated: 2018/11/06 10:01:32 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*des1;
	char	*src1;

	des1 = dest;
	src1 = (char *)src;
	i = 0;
	while (i < n)
	{
		des1[i] = src1[i];
		i++;
	}
	return (dest);
}
