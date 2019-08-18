/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 16:06:43 by dmolyboh          #+#    #+#             */
/*   Updated: 2018/11/14 22:54:57 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(const char *string1, const char *string2)
{
	int i;

	i = 0;
	while (string1[i] != '\0' || string2[i] != '\0')
	{
		if (string1[i] < string2[i] || string1[i] > string2[i])
			return ((unsigned char)string1[i] - (unsigned char)string2[i]);
		i++;
	}
	if (string1[i] != '\0')
		return (1);
	else if (string2[i] != '\0')
		return (-1);
	return (0);
}
