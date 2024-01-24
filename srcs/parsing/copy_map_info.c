/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_map_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraban <akaraban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:14:21 by narigi-e          #+#    #+#             */
/*   Updated: 2024/01/23 20:04:24 by akaraban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void  print_map(char **map)
{
	int i;

	i = 0;
	while (map[i] != NULL)
	{
		printf("%s\n", map[i]);
		i++;
	}
}

static void	open_file(char *file, int *fd)//may be changed
{
	*fd = open(file, O_RDONLY);
	if (*fd == -1)
		return (print_error("Couldn't open file.\n"));
}

static void	skip_lines(int fd, int lines_to_skip)
{
	int		i;
	char	*line;

	i = 0;
	while (i < lines_to_skip)
	{
		line = get_next_line(fd);
		free(line);
		i++;
	}
}

static void	allocate_map(t_vars *info)
{
	int	i;

	i = 0;
	info->map.map = malloc(sizeof(char *) * (info->map.height + 1));
	if (!info->map.map)
		return (print_error("Malloc failed."));
	info->map.map[info->map.height + 1] = NULL;
}

static void	fill_map(t_vars *info, int fd)
{
	int		i;
	char	*line;
	int 	size;

	i = 0;
	size = 0;
	while (i < info->map.height)
	{

		line = get_next_line(fd);
		if (!line)
			return (print_error("Couldn't read line.")); // newly added line 
		size = ft_strlen(line);
		info->map.map[i] = malloc(sizeof(char) * (size + 1));
		if (!info->map.map[i])
			return (print_error("Malloc failed."));
		ft_strcpy(info->map.map[i], line);
		free(line);
		i++;
	}
	info->map.map[i] = NULL;
}

static void	copy_map(t_vars *info, char *file)
{
	int	fd;
	
	if (info->map.player_count != 1)
		return (print_error("Invalid number of players."));
	open_file(file, &fd);
	skip_lines(fd, info->map.start_map_index);
	allocate_map(info);
	fill_map(info, fd); //test function
	close(fd);
}

int	copy_map_to_info(t_vars *info, char *file)
{
	copy_map(info, file);
	if (!info->map.map)
	{
		print_error("Couldn't copy map.");
		return (0);
	}
	print_map(info->map.map);
	return (1);
}
