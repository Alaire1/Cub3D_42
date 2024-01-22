#include "../../includes/cub3d.h"

static void ft_free_array(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
static int array_len(char **arr)
{
	int i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

static int	ft_isnumber2(const char *str) // have to change nem later
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i ++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i ++;
	}
	return (1);
}

int trgb_to_int(int t, int red, int green, int blue) //OxFF = 255
{
    return ((t & 0xFF) << 24) | ((red & 0xFF) << 16) | ((green & 0xFF) << 8) | (blue & 0xFF);
}


static int validate_rgb_values(char **arr)
{
    if (!ft_isnumber2(arr[0]) || !ft_isnumber2(arr[1]) || !ft_isnumber2(arr[2]))
    {
        print_error("Invalid RGB values.");
        ft_free_array(arr);
        return 0;
    }
    return 1;
}

static int validate_rgb_range(int *rgb)
{
    if (rgb[0] < 0 || rgb[0] > 255
        || rgb[1] < 0 || rgb[1] > 255
        || rgb[2] < 0 || rgb[2] > 255)
    {
        print_error("Invalid RGB combination.");
        return 0;
    }
    return 1;
}

static int	get_color_rgb(int *color, char **info)
{
    char	**arr;
    int		rgb[3];

    arr = ft_split(info[1], ',');
    if (array_len(arr) != 3)
    {
        print_error("Invalid RGB format.");
        ft_free_array(arr);
        return 0;
    }
    if (!validate_rgb_values(arr))
        return 0;
    rgb[0] = ft_atoi(arr[0]);
    rgb[1] = ft_atoi(arr[1]);
    rgb[2] = ft_atoi(arr[2]);
    ft_free_array(arr);
    if (!validate_rgb_range(rgb))
        return 0;
    *color = trgb_to_int(0, rgb[0], rgb[1], rgb[2]); // may be changed to just rgb
    return 1;
}

static int	get_image(t_vars *info, t_img *img, char *path)
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

static int save_textures(t_vars *info, char **arr) 
{
	int error_flag;

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
		error_flag = get_color_rgb(&info->map.fl_color, arr); //not written yet
	else if (!ft_strcmp(arr[0], "C"))
		error_flag = get_color_rgb(&info->map.ce_color ,arr);
	return (error_flag);
}

static int all_info_read(t_map *map)
{
	if (map->ce_color == -1|| map->fl_color == -1)
		return (0);
	if (!map->north.img || !map->south.img || !map->west.img|| !map->east.img)
		return (0);
	return (1);
}
static int is_texture_duplicated(t_map *map, char **arr)
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

static int is_form_valid(char **arr)
{
	if ((!ft_strcmp(arr[0], "NO")) && array_len(arr) != 2)
		return (print_error("Invalid texture NO format"), 0);
	else if (!ft_strcmp(arr[0], "SO") && array_len(arr) != 2)
		return (print_error("Invalid texture SO format"), 0);
	else if (!ft_strcmp(arr[0], "WE") && array_len(arr) != 2)
		return (print_error("Invalid texture WE format"), 0);
	else if (!ft_strcmp(arr[0], "EA") && array_len(arr) != 2)
		return (print_error("Invalid texture EA format"), 0);
	else if(!ft_strcmp(arr[0], "F") && array_len(arr) != 2)
		return (print_error("Invalid texture F format"), 0);
	else if(!ft_strcmp(arr[0], "C") && array_len(arr) != 2)
		return (print_error("Invalid texture C format"), 0);
	return (1);
}

static int check_textures(t_vars *info, char **array)
{
	if (!is_form_valid(array) || is_texture_duplicated(&info->map, array)
	 || !save_textures(info, array))
		return (0);
	return (1);
}

static int	get_map_info(t_vars *main, int fd)
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
			array = ft_split(line, ' ');
			if (check_textures(main, array) == 0)
				return (ft_free_array(array), 0);
			ft_free_array(array);
		}
		free(line);
	}
	return (1);
}

static int read_textures(t_vars *info, int fd) // needs to be chnaged very useless
{
    if (!get_map_info(info, fd))
        return (0);
    return (1);
}


static int check_walls(t_vars *info) //seems to work but will do more tests
{
	int i;
	int j;

	i = 0;
	while (i < info->map.height)
	{
		j = 0;
		while (j < info->map.width)
		{
			if (info->map.map[i][j] == '0')
			{
				if (i == 0 || i == info->map.height - 1 || j == 0 || j == info->map.width - 1)
				{
					print_error("Map is not closed.\n");
					return (0);
				}
				if (info->map.map[i - 1][j] == ' ' || info->map.map[i + 1][j] == ' ' || info->map.map[i][j - 1] == ' ' || info->map.map[i][j + 1] == ' ')
				{
					print_error("Map is not closed.\n");
					return (0);
				}
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	importing_map(t_vars *vars, char *file)
{
	int		fd;

	fd = open(file, O_RDONLY);
    if (fd == -1)
	{
		print_error("Couldn't open file.\n");
		return (0);
	}
	if (!read_textures(vars, fd) || !check_map_size(vars, fd))
	{
		close(fd);
		return (0);
	}
	close(fd);
	if (!copy_map_to_info(vars, file))
	{
		return (0);
	}
	if (check_walls(vars) == 0)	
		return (0);
	getting_player_position(vars);
	return (1);
}
