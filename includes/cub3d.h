/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraban <akaraban.student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:46:39 by narigi-e          #+#    #+#             */
/*   Updated: 2024/04/23 21:41:34 by akaraban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <errno.h>
# include <sys/time.h>
# include "../Libft/libft.h"
# include "../mlx_linux/mlx.h"

# define NAME "Cub3D"

# define RADIAN_INC		0.06

# define RED 			"\x1B[0;31m"
# define RESET 			"\x1B[0m"

# define ERROR 			1
# define SUCCESS		0

/***********************[ Components ]***********************/
# define SPACE			' '
# define EMPTY_SPACE	'0'
# define WALL			'1'
# define P_NORTH		'N'
# define P_SOUTH		'S'
# define P_EAST			'E'
# define P_WEST			'W'
# define HIT_WALLS		"1"

/***********************[ Enumeration ]***********************/
// enum e_keycodes //keycodes for mac
// {
// 	KEY_ESC = 53,
// 	KEY_A = 0,
// 	KEY_W = 13,
// 	KEY_D = 2,
// 	KEY_S = 1,
// 	KEY_LEFT = 123,
// 	KEY_UP = 126,
// 	KEY_RIGHT = 124,
// 	KEY_DOWN = 125
// };
enum e_keycodes //keycodes for linux
{
    KEY_ESC = 0xFF1B,
    KEY_A = 0x61,
    KEY_W = 0x77,
    KEY_D = 0x64,
    KEY_S = 0x73,
    KEY_LEFT = 0xFF51,
    KEY_UP = 0xFF52,
    KEY_RIGHT = 0xFF53,
    KEY_DOWN = 0xFF54
};

enum e_window
{
	WIDTH = 850,
	HEIGHT = 500,
	FPS_X = 5,
	FPS_Y = 15
};

enum e_player
{
	SPEED = 4,
	ROT_SPEED = 3,
	FOV	= 75
};

/************************[ Structers ]************************/
typedef struct s_dim
{
	double	width;
	double	height;
}	t_dim;

typedef struct s_coor
{
	double	x;
	double	y;
}	t_coor;

typedef struct s_render
{
	double			degree;
	double			angle;
	t_coor			hit_wall;
	int				direc;
	double			dist;
	t_dim			wall_dim;
	double			wall_orig_height;
	struct s_render	*next;
}	t_render;

typedef struct s_content
{
	int	wall;
	int	player;
}	t_content;

typedef struct s_player
{
	t_coor	pos;
	double	angle;
	t_coor	dir;
	t_coor	move;
	double	rotate;
}	t_player;

typedef struct s_img
{
	void	*img;
	int		*data;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_map
{
	char	**map;
	int		ce_color;
	int		fl_color;
	int		width;
	int		height;
	int		start_map_index;
	int		player_count;
	t_img	north;
	t_img	south;
	t_img	west;
	t_img	east;
}	t_map;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	img;
	int		fps;
	double	fspeed;
}	t_mlx;

typedef struct s_main
{
	t_mlx		mlx;
	t_map		map;
	t_player	player;
}	t_main;

/************************* Parsing *************************/
//check_input_validity.c
void	print_error(char *error);
int		check_for_valid_input(char **argv, int argc);

//copy_map_info.c
int		copy_map_to_info(t_main *info, char *file);

//get_map_size.c
int		get_map_size(t_map *map, int fd);

//import_map.c
int		importing_map(t_main *vars, char *file);
int		map_check_validity(t_map *map);
int		valid_map(char **map, int i, int j);

//init_structs.c
void	init_main_struct(t_main *info);
void	init_player(t_player *player);

//parse_map.c
int		check_map_size(t_main *info, int fd);
int		check_after_map(int fd);

//read_textures.c
int		read_textures(t_main *info, int fd);
int		get_map_info(t_main *main, int fd);
int		check_textures(t_main *info, char **array);
int		is_form_valid(char **arr);
int		is_texture_duplicated(t_map *map, char **arr);

//save_textures.c
int		all_info_read(t_map *map);
int		save_textures(t_main *info, char **arr);
int		get_image(t_main *info, t_img *img, char *path);
int		get_color_rgb(int *color, char **info);
int		validate_rgb_range(int *rgb);

//utils_1.c
void	ft_free_array(char **arr);
int		array_len(char **arr);
int		ft_isnumber2(const char *str);
int		trgb_to_int(int t, int red, int green, int blue);
int		validate_rgb_values(char **arr);

//utils_2.c
int		empty_line(char *line);
int		only_spaces(char *line);

/***************[ Player ]***************/
//getting_player_position.c
void	getting_player_position(t_main *info);

//player_movements.c
int		key_release(int keycode, t_main *info);
int		pressing_keys(int keycode, t_main *info);
void	moving_player(t_main *info);

/***************[ Rendering ]***************/
//drawing_floor_and_ceilling.c
void	drawing_floor_and_ceilling(t_main *info);

//get_hit_wall.c
t_coor	ft_get_hit_wall(t_main *info, t_coor start_pos,
			double angle, int *direction);

//rendering_3d_scenes.c
void	rendering_3d_scenes(t_main *info);

//rendering_frames.c
int		rendering_frames(t_main *info);
int		initializing_images(t_main *info);

/***************[ Utils ]***************/
//exiting_game.c
int		exiting_game(t_main *info, int exit_status);

//getting_current_time.c
long	getting_current_time(void);

//getting_distances.c
double	getting_distance(t_coor point1, t_coor point2);

//radian_calculations.c
double	degree_to_radian(double degree);
double	radian_to_degree(double radian);
double	radian_calculations(double radian, double amout);

#endif
