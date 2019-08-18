/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 11:29:44 by dmolyboh          #+#    #+#             */
/*   Updated: 2018/11/19 02:21:06 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmap(char const *s, char (*f)(char))
{
	char	*ss;
	int		i;

	i = 0;
	ss = NULL;
	if (s != NULL)
	{
		ss = ft_memalloc(ft_strlen((char *)s) + 1);
		if (ss == NULL)
			return (NULL);
		while (s[i] != '\0')
		{
			ss[i] = f(s[i]);
			i++;
		}
		ss[i] = '\0';
	}
	return (ss);
}
