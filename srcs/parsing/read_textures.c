/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraban <akaraban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:51:31 by narigi-e          #+#    #+#             */
/*   Updated: 2024/01/26 13:12:42 by akaraban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_texture_duplicated(t_map *map, char **arr)
{
	if (map->north.img != NULL && !ft_strcmp(arr[0], "NO"))
		return (print_error("Texture NO duplicated."), 1);
	else if (map->south.img != NULL && !ft_strcmp(arr[0], "SO"))
		return (print_error("Texture SO duplicated."), 1);
	else if (map->west.img != NULL && !ft_strcmp(arr[0], "WE"))
		return (print_error("Texture WE duplicated."), 1);
	else if (map->east.img != NULL && !ft_strcmp(arr[0], "EA"))
		return (print_error("Texture EA duplicated."), 1);
	else if (map->fl_color != -1 && !ft_strcmp(arr[0], "F"))
		return (print_error("Texture F duplicated."), 1);
	else if (map->ce_color != -1 && !ft_strcmp(arr[0], "C"))
		return (print_error("Texture C duplicated."), 1);
	return (0);
}

int	is_form_valid(char **arr)
{
	if ((!ft_strcmp(arr[0], "NO")) && array_len(arr) != 2)
		return (print_error("Invalid texture NO format"), 0);
	else if (!ft_strcmp(arr[0], "SO") && array_len(arr) != 2)
		return (print_error("Invalid texture SO format"), 0);
	else if (!ft_strcmp(arr[0], "WE") && array_len(arr) != 2)
		return (print_error("Invalid texture WE format"), 0);
	else if (!ft_strcmp(arr[0], "EA") && array_len(arr) != 2)
		return (print_error("Invalid texture EA format"), 0);
	else if (!ft_strcmp(arr[0], "F") && array_len(arr) != 2)
		return (print_error("Invalid texture F format"), 0);
	else if (!ft_strcmp(arr[0], "C") && array_len(arr) != 2)
		return (print_error("Invalid texture C format"), 0);
	return (1);
}

int	check_textures(t_main *info, char **array)
{
	if (!is_form_valid(array) || is_texture_duplicated(&info->map, array)
		|| !save_textures(info, array))
		return (0);
	return (1);
}

int	get_map_info(t_main *main, int fd)
{
	char	*line;
	char	**array;

	while (!all_info_read(&main->map))
	{
		line = get_next_line(fd);
		if (!line)
			return (print_error("Missing textures.\n"), 0);
		if (*line)
		{
			main->map.start_map_index++;
			if (!empty_line(line))
			{
				array = ft_split(line, ' ');
				if (check_textures(main, array) == 0)
					return (ft_free_array(array), free(line), 0);
				ft_free_array(array);
			}
		}
		else
			main->map.start_map_index++;
		free(line);
	}
	return (1);
}

int	read_textures(t_main *info, int fd)
{
	if (!get_map_info(info, fd))
		return (0);
	return (1);
}
