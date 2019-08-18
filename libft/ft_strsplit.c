/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 07:39:24 by dmolyboh          #+#    #+#             */
/*   Updated: 2018/11/19 01:36:43 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int		ft_count_arr(char const *s, char c)
{
	int			a;
	int			i;

	i = 0;
	a = 1;
	while (s[i] == c && s[i])
		i++;
	if (s[i++] == '\0')
		return (a);
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			while (s[i] == c)
				i++;
			a++;
		}
		else
			i++;
	}
	return (a + 1);
}

static void		*ft_count_char(char const *s, char c)
{
	int			i;
	int			j;
	char		*rezult;

	i = 0;
	j = 0;
	while (s[i] && s[i] != c)
		i++;
	rezult = ft_memalloc(i + 1);
	if (rezult == NULL)
		return (NULL);
	while (j < i)
	{
		rezult[j] = s[j];
		j++;
	}
	rezult[j] = '\0';
	return (rezult);
}

static char		**ft_creater_arr(char **s, int count)
{
	s = (char**)malloc((sizeof(char *) * (count)));
	if (s == NULL)
		return (NULL);
	s[count - 1] = NULL;
	return (s);
}

char			**ft_strsplit(char const *s, char c)
{
	char		**ss;
	int			a;
	int			i;

	i = 0;
	ss = NULL;
	if (s == NULL || *s == '\0')
		return (ft_creater_arr(ss, 1));
	a = ft_count_arr(s, c);
	if ((ss = ft_creater_arr(ss, a)) == NULL)
		return (NULL);
	while (i != a)
	{
		if (*s == c)
			s++;
		else if (*s == '\0')
			ss[i++] = NULL;
		else
		{
			ss[i++] = ft_count_char(s, c);
			while (*s != c && *s != '\0')
				s++;
		}
	}
	return (ss);
}
