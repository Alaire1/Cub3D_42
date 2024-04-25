/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraban <akaraban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:36:27 by narigi-e          #+#    #+#             */
/*   Updated: 2024/01/22 17:33:24 by akaraban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*get_fd_content(int fd, t_list **fd_list)
{
	t_list	*holder;

	holder = *fd_list;
	while (holder)
	{
		if (holder->fd == fd)
			return (holder->content);
		holder = holder->next;
	}
	return ("");
}

static void	set_fd_content(
	int fd, t_list **fd_list, char content[BUFFER_SIZE + 1]
	)
{
	t_list	*holder;
	t_list	*new_list;

	holder = *fd_list;
	while (holder)
	{
		if (holder->fd == fd)
		{
			ft_strcpy(holder->content, content);
			return ;
		}
		holder = holder->next;
	}
	new_list = ft_calloc(1, sizeof(t_list));
	if (new_list == NULL)
		return ;
	new_list->fd = fd;
	ft_strcpy(new_list->content, content);
	new_list->next = NULL;
	holder = *fd_list;
	*fd_list = new_list;
	(*fd_list)->next = holder;
}

static void	del_fd_content(int fd, t_list **fd_list)
{
	t_list	*holder;
	t_list	*prev_holder;

	holder = *fd_list;
	if (holder && holder->fd == fd)
	{
		*fd_list = (*fd_list)->next;
		free(holder);
		return ;
	}
	while (holder)
	{
		if (holder->fd == fd)
		{
			prev_holder->next = holder->next;
			free(holder);
			return ;
		}
		prev_holder = holder;
		holder = holder->next;
	}
	return ;
}

static int	read_next_line(
	int fd, t_list **fd_list, char **next_line, char buffer[BUFFER_SIZE + 1]
	)
{
	int		ret;

	ft_strcpy(buffer, get_fd_content(fd, fd_list));
	if (!*buffer)
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret >= 0)
			buffer[ret] = '\0';
		if (ret < 1)
		{
			if (*next_line && !**next_line)
				*next_line = ft_free(*next_line);
			return (del_fd_content(fd, fd_list), 0);
		}
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static t_list	*fd_list;
	char			*next_line;
	char			buffer[BUFFER_SIZE + 1];
	char			*has_newline;
	size_t			len;

	next_line = ft_strdup("");
	if (next_line == NULL)
		return (NULL);
	while (read_next_line(fd, &fd_list, &next_line, buffer))
	{
		len = ft_strlen(buffer);
		has_newline = ft_strchr(buffer, '\n');
		if (has_newline)
			len -= ft_strlen(has_newline);
		next_line = ft_strnadd(next_line, buffer, len);
		if (next_line == NULL)
			break ;
		if (has_newline)
			len += 1;
		set_fd_content(fd, &fd_list, buffer + len);
		if (has_newline)
			break ;
	}
	return (next_line);
}
