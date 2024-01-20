
#include "../../includes/cub3d.h"

static int check_player(char c, t_map *map)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		map->player_count++;
		if (map->player_count > 1)
		{
			print_error("Too many players.\n");
			return (1);
		}
	}
	return (0);
}

static int map_valid_content(char *line, t_map *map)
{
	int i;

	i = 0;

	while (line[i] != 0)
	{
		if (check_player(line[i], map))
			return (0);
		if (line[i] != '0' && line[i] != '1' 
		&& line[i] != '2' && line[i] != 'N'
		 && line[i] != 'S' && line[i] != 'W' 
		 && line[i] != 'E' && line[i] != ' ')
		{
			print_error("Invalid map content.\n");
			return (0);
		}
		i++;
	}
	return (1);
}

static int only_spaces(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

static int empty_line(char *line)
{
	int i;

	i = 0;
	if (ft_strcmp(line , "\n") == 0)
		return (1);
	else if (ft_strcmp(line , "") == 0)
		return (1);
	else if (only_spaces(line))
		return (1);
	return (0);
}

static int get_map_size(t_map *map, int fd)
{
	char	*line;
	int		i;
	int null_flag;

	i = 0;
	null_flag = 0;
	while (!null_flag) // while loop condition may need to be changed since it's basically like while (1)
	{
		line = get_next_line(fd);
		if (!line) //that first so if there's no line it will break
		{
			null_flag = 1;
			break;
		}
		else if (empty_line(line))
		{
			map->start_map_index++;
			if (map->height != 0 && map->width != 0)
				break; 
		}
		if (*line)
		{
			if (map_valid_content(line, map) == 0) //changed to not copy map, if there are invalid chars
				return (0);
			// map_has_started = 1;
			map->height++;
			if ((size_t)map->width < ft_strlen(line))
				map->width = ft_strlen(line);
		}
		i++;
	}
	return (1);
}

int check_map_size(t_vars *info, int fd)
{
    if (get_map_size(&info->map, fd) == 0)
        return (0);
    if (!info->map.width || !info->map.height)
    {
        print_error("Invalid map size.\n");
        return(0);
    }
    return(1);
}