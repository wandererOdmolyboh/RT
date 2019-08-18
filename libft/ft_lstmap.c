/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 20:32:25 by dmolyboh          #+#    #+#             */
/*   Updated: 2018/11/18 20:16:34 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*q_list;
	t_list	*head_list;

	if (!lst || !f)
		return (NULL);
	q_list = f(lst);
	head_list = q_list;
	while (lst->next)
	{
		lst = lst->next;
		q_list->next = f(lst);
		q_list = q_list->next;
	}
	q_list->next = NULL;
	return (head_list);
}
