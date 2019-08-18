/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 10:55:30 by dmolyboh          #+#    #+#             */
/*   Updated: 2018/12/09 01:45:27 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	a;

	if (!s)
		return (NULL);
	a = ft_strlen((char *)s);
	s = s + a;
	while (a != 0)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s--;
		a--;
	}
	if (*s == (unsigned char)c)
		return ((char *)s);
	return (NULL);
}
