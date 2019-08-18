/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 11:15:49 by dmolyboh          #+#    #+#             */
/*   Updated: 2018/11/19 02:21:17 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ss;
	unsigned int	i;

	i = 0;
	ss = NULL;
	if (s != NULL)
	{
		ss = ft_memalloc(ft_strlen((char *)s) + 1);
		if (ss == NULL)
			return (NULL);
		while (s[i] != '\0')
		{
			ss[i] = f(i, s[i]);
			i++;
		}
		ss[i] = '\0';
	}
	return (ss);
}
