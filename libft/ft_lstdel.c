/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 18:15:00 by dmolyboh          #+#    #+#             */
/*   Updated: 2018/11/14 20:11:39 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*p;

	if (alst || *alst)
		while (*alst)
		{
			p = (*alst)->next;
			del((*alst)->content, (*alst)->content_size);
			free(*alst);
			*alst = p;
		}
}
