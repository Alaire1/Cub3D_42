/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraban <akaraban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:17:30 by narigi-e          #+#    #+#             */
/*   Updated: 2024/01/25 12:40:03 by akaraban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	check_near_item(char **map, int i, int j)
{
	if (map[i][j + 1] && ft_strchr("0NSEW", map[i][j + 1]))
		return (1);
	else if (j - 1 >= 0 && ft_strchr("0NSEW", map[i][j - 1]))
		return (1);
	else if (map[i + 1] && j < (int)ft_strlen(map[i + 1])
		&& ft_strchr("0NSEW", map[i + 1][j]))
		return (1);
	else if (i - 1 >= 0 && j < (int)ft_strlen(map[i - 1])
		&& ft_strchr("0NSEW", map[i - 1][j]))
		return (1);
	return (0);
}

static int	check_space(char **map, int i, int j)
{
	if (!map[i][j + 1] || (map[i][j + 1]
		&& map[i][j + 1] == SPACE))
		return (1);
	else if (j - 1 < 0
		|| (j - 1 >= 0 && map[i][j - 1] == SPACE))
		return (1);
	else if (!map[i + 1]
		|| (map[i + 1] && j >= (int)ft_strlen(map[i + 1]))
		|| (map[i + 1] && j < (int)ft_strlen(map[i + 1])
			&& map[i + 1][j] == SPACE))
		return (1);
	else if (i - 1 < 0
		|| (i - 1 >= 0 && j >= (int)ft_strlen(map[i - 1]))
		|| (i - 1 >= 0 && j < (int)ft_strlen(map[i - 1])
			&& map[i - 1][j] == SPACE))
		return (1);
	return (0);
}

int	valid_map(char **map, int i, int j)
{
	if (map[i][j] == SPACE && check_near_item(map, i, j))
		return (print_error("Misplaced empty space."), 0);
	else if (ft_strchr("0NSEW", map[i][j]))
	{
		if (check_space(map, i, j))
		{
			if (map[i][j] == EMPTY_SPACE)
				print_error("Misplaced empty space.");
			else
				print_error("Misplaced player position");
			return (0);
		}
	}
	return (1);
}

int	map_check_validity(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (map->map[i][j] != '\0')
		{
			if (ft_strchr(" 0NSEW", map->map[i][j]))
			{
				if (!valid_map(map->map, i, j))
					return (0);
			}
			j ++;
		}
		i ++;
	}
	return (1);
}

int	importing_map(t_main *info, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (print_error("Couldn't open file.\n"), 0);
	if (!read_textures(info, fd) || !check_map_size(info, fd))
		return (close(fd), 0);
	close(fd);
	if (!copy_map_to_info(info, file))
		return (0);
	if (map_check_validity(&info->map) == 0)
		return (0);
	getting_player_position(info);
	return (1);
}
