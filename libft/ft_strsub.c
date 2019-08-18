/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 11:18:21 by dmolyboh          #+#    #+#             */
/*   Updated: 2018/12/09 01:40:12 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	unsigned char	*c;
	int				i;

	i = 0;
	if (s == NULL)
		return (NULL);
	c = ft_memalloc(len + 1);
	if (c == NULL)
		return (NULL);
	while (s[start] != '\0' && (size_t)i < len)
	{
		c[i] = s[start];
		i++;
		start++;
	}
	c[i] = '\0';
	return ((char *)c);
}
