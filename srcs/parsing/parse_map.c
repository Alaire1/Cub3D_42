/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraban <akaraban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:26:46 by narigi-e          #+#    #+#             */
/*   Updated: 2024/01/24 19:30:44 by akaraban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_after_map(int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		else if (empty_line(line))
		{
			free(line);
			continue ;
		}
		else
			return (free(line), 0);
	}
	return (1);
}

int	check_map_size(t_main *info, int fd)
{
	if (get_map_size(&info->map, fd) == 0 || check_after_map(fd) == 0)
	{
		print_error("Invalid map.");
		return (0);
	}
	if (info->map.width == 0 || info->map.height == 0)
	{
		print_error("Invalid map size.");
		return (0);
	}
	return (1);
}
