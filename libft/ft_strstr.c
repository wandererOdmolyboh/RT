/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 13:34:37 by dmolyboh          #+#    #+#             */
/*   Updated: 2019/08/01 16:22:13 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int nr[3];

	nr[0] = 0;
	if (ft_strlen((char *)needle) == 0)
		return ((char *)haystack);
	if (haystack == NULL || needle == NULL)
		return (NULL);
	while (haystack[nr[0]] || haystack[nr[0]] == '\0')
	{
		nr[2] = nr[0];
		nr[1] = 0;
		if (needle[nr[1]] == haystack[nr[0]])
			while (needle[nr[1]] == haystack[nr[0]]
					&& (needle[nr[1]] != '\0' || haystack[nr[0]] != '\0'))
			{
				nr[0]++;
				nr[1]++;
			}
		nr[0] = nr[2];
		if (needle[nr[1]] == '\0')
			return ((char *)(haystack + nr[0]));
		if (!haystack[nr[0]++])
			return (NULL);
	}
	return (NULL);
}
