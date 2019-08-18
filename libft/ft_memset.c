/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 18:49:13 by dmolyboh          #+#    #+#             */
/*   Updated: 2018/12/01 20:19:28 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*p;

	if (len == 0)
		return (b);
	i = 0;
	p = (unsigned char *)b;
	while (i < (size_t)len)
	{
		p[i] = (char)c;
		i++;
	}
	return (b);
}
