/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 18:12:05 by dmolyboh          #+#    #+#             */
/*   Updated: 2018/11/14 23:12:49 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char *q;
	unsigned char *qq;

	q = (unsigned char *)s1;
	qq = (unsigned char *)s2;
	while (n != 0)
	{
		if (*q != *qq)
			return (*q - *qq);
		if (n)
		{
			q++;
			qq++;
		}
		n--;
	}
	return (0);
}
