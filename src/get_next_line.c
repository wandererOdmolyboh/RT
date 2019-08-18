/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanderer <wanderer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 02:33:25 by dmolyboh          #+#    #+#             */
/*   Updated: 2019/08/15 19:42:14 by wanderer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

static t_lst		*create_list(t_lst **list, int fd)
{
	if ((*list = ft_memalloc(sizeof(t_lst))) == NULL)
		return (NULL);
	(*list)->fd = fd;
	return (*list);
}

static t_lst		*add_list(t_lst **list, int fd)
{
	t_lst			*tmp;
	t_lst			*head;

	head = *list;
	if (!*list)
		return (create_list(list, fd));
	while (head != NULL)
	{
		if (head->fd == fd)
			return (head);
		head = head->next;
	}
	create_list(&tmp, fd);
	tmp->next = *list;
	*list = tmp;
	return (tmp);
}

static int			add_on_gnl(t_lst *new, char **line, char *buf)
{
	char			*tmp;

	if (new->line_ret && (buf = ft_strchr(new->line_ret, '\n')))
	{
		*line = ft_strsub(new->line_ret, 0, buf - new->line_ret);
		tmp = new->line_ret;
		new->line_ret = ft_strdup(buf + 1);
		free(tmp);
		return (1);
	}
	else if (!buf && *new->line_ret && (*line = ft_strdup(new->line_ret)))
	{
		ft_strdel(&new->line_ret);
		return (1);
	}
	return (0);
}

int					get_next_line(const int fd, char **line)
{
	static t_lst	*head;
	t_lst			*new;
	char			*buf;
	char			*tmp;
	int				n;

	if (fd < 0 || line == NULL || BUFF_SIZE < 1 ||
	read(fd, NULL, 0) < 0 || (!(new = add_list(&head, fd))) ||
	(!(buf = malloc(BUFF_SIZE + 1))))
		return (put_error("Something wrong in read\n"));
	if (!(ft_strchr(new->line_ret, '\n')))
		while ((n = read(fd, buf, BUFF_SIZE)) > 0)
		{
			buf[n] = '\0';
			tmp = new->line_ret;
			new->line_ret = ft_strjoin(new->line_ret, buf);
			free(tmp);
			if (ft_strrchr(buf, '\n'))
				break ;
		}
	free(buf);
	return (add_on_gnl(new, line, buf));
}
