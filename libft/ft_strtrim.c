/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 15:39:56 by dmolyboh          #+#    #+#             */
/*   Updated: 2018/11/18 19:37:00 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s)
{
	char	*ss;
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	if (*s == '\0')
		return ((char *)s);
	len = ft_strlen((char *)s) - 1;
	while ((s[i] == ' ' || s[i] == '\n' || s[i] == '\t') && i < len)
		i++;
	while ((s[len] == ' ' || s[len] == '\n' || s[len] == '\t') && len >= i)
		len--;
	if ((ss = ft_memalloc(len - i + 2)) == NULL)
		return (ss);
	while (i <= len)
		ss[j++] = s[i++];
	return (ss);
}
