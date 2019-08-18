/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 13:32:13 by dmolyboh          #+#    #+#             */
/*   Updated: 2018/11/15 10:54:11 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_strncmp(const char *string1, const char *string2, size_t num)
{
	size_t i;

	i = 0;
	if (num == 0)
		return (0);
	while (string1[i] != '\0' || string2[i] != '\0')
	{
		if (string1[i] != string2[i] && i < num)
			return ((unsigned char)string1[i] - (unsigned char)string2[i]);
		i++;
	}
	if (string1[i] != '\0')
		return (1);
	else if (string2[i] != '\0')
		return (-1);
	return (0);
}
