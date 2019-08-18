/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 17:21:06 by dmolyboh          #+#    #+#             */
/*   Updated: 2018/11/19 02:12:01 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *list;

	if ((list = (t_list *)ft_memalloc(sizeof(t_list))) == NULL)
		return (NULL);
	if (content != NULL)
	{
		if ((list->content = ft_memalloc(content_size)) == NULL)
			return (NULL);
		list->content = ft_memcpy(list->content, (void *)content, content_size);
		list->content_size = content_size;
	}
	else
	{
		list->content = NULL;
		list->content_size = 0;
	}
	list->next = NULL;
	return (list);
}
