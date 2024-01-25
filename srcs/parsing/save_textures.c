/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraban <akaraban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:51:35 by narigi-e          #+#    #+#             */
/*   Updated: 2024/01/25 13:09:15 by akaraban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	validate_rgb_range(int *rgb)
{
	if (rgb[0] < 0 || rgb[0] > 255
		|| rgb[1] < 0 || rgb[1] > 255
		|| rgb[2] < 0 || rgb[2] > 255)
	{
		print_error("Invalid RGB combination.");
		return (0);
	}
	return (1);
}

int	get_color_rgb(int *color, char **info)
{
	char	**arr;
	int		rgb[3];

	arr = ft_split(info[1], ',');
	if (array_len(arr) != 3)
	{
		print_error("Invalid RGB format.");
		ft_free_array(arr);
		return (0);
	}
	if (!validate_rgb_values(arr))
		return (0);
	rgb[0] = ft_atoi(arr[0]);
	rgb[1] = ft_atoi(arr[1]);
	rgb[2] = ft_atoi(arr[2]);
	ft_free_array(arr);
	if (!validate_rgb_range(rgb))
		return (0);
	*color = trgb_to_int(0, rgb[0], rgb[1], rgb[2]);
	return (1);
}

int	get_image(t_main *info, t_img *img, char *path)
{
	img->img = mlx_xpm_file_to_image(info->mlx.mlx, path,
			&img->width, &img->height);
	if (img->img == 0)
	{
		print_error("Invalid texture path");
		return (0);
	}
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp,
			&img->line_len, &img->endian);
	if (!img->data)
	{
		print_error("Image data isn't valid");
		return (0);
	}
	return (1);
}

int	save_textures(t_main *info, char **arr)
{
	int	error_flag;

	error_flag = 0;
	if (!ft_strcmp(arr[0], "NO"))
		error_flag = get_image(info, &info->map.north, arr[1]);
	else if (!ft_strcmp(arr[0], "SO"))
		error_flag = get_image(info, &info->map.south, arr[1]);
	else if (!ft_strcmp(arr[0], "WE"))
		error_flag = get_image(info, &info->map.west, arr[1]);
	else if (!ft_strcmp(arr[0], "EA"))
		error_flag = get_image(info, &info->map.east, arr[1]);
	else if (!ft_strcmp(arr[0], "F"))
		error_flag = get_color_rgb(&info->map.fl_color, arr);
	else if (!ft_strcmp(arr[0], "C"))
		error_flag = get_color_rgb(&info->map.ce_color, arr);
	return (error_flag);
}

int	all_info_read(t_map *map)
{
	if (map->ce_color == -1 || map->fl_color == -1)
		return (0);
	if (!map->north.img || !map->south.img || !map->west.img || !map->east.img)
		return (0);
	return (1);
}
