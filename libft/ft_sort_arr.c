/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 19:50:21 by dmolyboh          #+#    #+#             */
/*   Updated: 2018/11/19 01:01:59 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_sort_arr(int *l, int *r)
{
	int	*tmp;

	if (!r && !l && r - l <= 1)
		return ;
	tmp = r;
	while (l < r)
	{
		while (r > l)
		{
			if (*l > *r)
				ft_swap(l, r);
			r--;
		}
		r = tmp;
		l++;
	}
}
