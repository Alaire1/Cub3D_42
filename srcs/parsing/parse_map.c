/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraban <akaraban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:26:46 by narigi-e          #+#    #+#             */
/*   Updated: 2024/01/24 15:11:20 by akaraban         ###   ########.fr       */
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

static int	only_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}
int	empty_line(char *line)
{
	if (ft_strcmp(line, "\n") == 0)
		return (1);
	else if (ft_strcmp(line, "") == 0)
		return (1);
	else if (only_spaces(line))
		return (1);
	return (0);
}

static int	get_map_size(t_map *map, int fd)
{
    char	*line;

    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break ;
        else if (empty_line(line) && map->height == 0 && map->width == 0)
        {
			map->start_map_index++;
            free(line);
            continue;
        }
        else if (*line && !empty_line(line))
        {
            if (map_valid_content(line, map) == 0)
                return (free(line), 0);
            map->height++;
            if ((size_t)map->width < ft_strlen(line))
                map->width = ft_strlen(line);
        }
		else
			break ;
        free(line);
    }
	map->start_map_index++;
    if (line != NULL)
        free(line);
    return (1);
}


int check_after_map(int fd)
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
			continue;
		}
		else
			return (free(line), 0);
	}
	return (1);
}

int	check_map_size(t_vars *info, int fd)
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
