/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 20:37:44 by dmolyboh          #+#    #+#             */
/*   Updated: 2018/12/08 16:13:57 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_strdup(const char *c)
{
	char	*p;
	size_t	a;
	size_t	i;

	if (c == NULL)
		return (NULL);
	i = 0;
	a = ft_strlen((char *)c);
	p = ft_memalloc(a + 1);
	if (p == NULL)
		return (NULL);
	while (i != a)
	{
		p[i] = c[i];
		i++;
	}
	return (p);
}
