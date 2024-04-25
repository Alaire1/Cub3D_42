/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraban <akaraban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:26:46 by akaraban          #+#    #+#             */
/*   Updated: 2024/01/26 13:13:23 by akaraban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	check_player(char c, t_map *map)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		map->player_count++;
		if (map->player_count > 1)
		{
			print_error("Too many players.");
			return (1);
		}
	}
	return (0);
}

static int	map_valid_content(char *line, t_map *map)
{
	int	i;

	i = 0;
	while (line[i] != 0)
	{
		if (check_player(line[i], map))
			return (0);
		if (line[i] != '0' && line[i] != '1'
			&& line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'W' && line[i] != 'E'
			&& line[i] != ' ')
		{
			print_error("Invalid map content.");
			return (0);
		}
		i++;
	}
	return (1);
}

static char	*skip_empty_lines(t_map *map, int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line || !empty_line(line) || (map->height != 0 && map->width != 0))
			return (line);
		map->start_map_index++;
		free(line);
	}
}

static int	process_map_lines(t_map *map, char *line, int fd)
{
	while (line)
	{
		if (empty_line(line))
		{
			free(line);
			break ;
		}
		if (!map_valid_content(line, map))
		{
			free(line);
			return (0);
		}
		map->height++;
		if ((size_t)map->width < ft_strlen(line))
			map->width = ft_strlen(line);
		free(line);
		line = get_next_line(fd);
	}
	return (1);
}

int	get_map_size(t_map *map, int fd)
{
	char	*line;
	int		result;

	result = 0;
	line = skip_empty_lines(map, fd);
	if (!line)
		return (0);
	result = process_map_lines(map, line, fd);
	return (result);
}
