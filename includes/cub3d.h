/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraban <akaraban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:46:39 by narigi-e          #+#    #+#             */
/*   Updated: 2024/01/23 15:48:30 by akaraban         ###   ########.fr       */
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
# include "../mlx/mlx.h"

# define USAGE			"Usage: ./cub3d <file.cub>"
# define RADIAN_INC		0.06

# define RED 			"\x1B[0;31m"
# define RESET 			"\x1B[0m"

# define ERROR 			1
# define SUCCESS		0

/***********************[ Components ]***********************/
# define SPACE			' '
# define EMPTY_SPACE	'0'
# define WALL			'1'
# define C_DOOR			'2'
# define O_DOOR			'3'
# define P_NORTH		'N'
# define P_SOUTH		'S'
# define P_EAST			'E'
# define P_WEST			'W'
# define HIT_WALLS		"1"

/***********************[ Enumeration ]***********************/
enum e_keycodes
{
	KEY_ESC = 53,
	KEY_A = 0,
	KEY_W = 13,
	KEY_D = 2,
	KEY_S = 1,
	KEY_LEFT = 123,
	KEY_UP = 126,
	KEY_RIGHT = 124,
	KEY_DOWN = 125
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
	MOUSE_ROT_SPEED = 5,
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

typedef struct s_vars
{
	t_mlx		mlx;
	t_map		map;
	t_player	player;
}	t_vars;

/**************************[ Utils ]**************************/
long	getting_current_time(void);
int		trgb_to_int(int t, int red, int green, int blue);
double	getting_distance(t_coor poin1, t_coor point2);
double	radian_to_degree(double radian);
double	degree_to_radian(double degree);
double	radian_calculations(double radian, double amout);

/*************************[ Parsing ]*************************/
int		empty_line(char *line);
int		check_for_valid_input(char **argv, int argc); //my function
void	print_error(char *error); //my function // needs to be taken to different file
int		importing_map(t_vars *vars, char *file);
int		ft_parse_textures(t_vars *vars, int fd);
int		ft_get_textures(t_vars *vars, char **info);
int		ft_component_surroundings(char **map, int i, int j);
int		check_map_size(t_vars *info, int fd); //my function
int		copy_map_to_info(t_vars *info, char *file); //my function
int		check_walls(t_map *map);
int		importing_map(t_vars *vars, char *file);

/***************[ utils_1 ]***************/
void	ft_free_array(char **arr);
int		array_len(char **arr);
int		ft_isnumber2(const char *str);
int		trgb_to_int(int t, int red, int green, int blue);
int		validate_rgb_values(char **arr);

/***************[ utils_2 ]***************/
int		is_texture_duplicated(t_map *map, char **arr);
int		is_form_valid(char **arr);
int		check_textures(t_vars *info, char **array);
int		get_map_info(t_vars *main, int fd);
int		read_textures(t_vars *info, int fd);

/***************[ utils_3 ]***************/
int		validate_rgb_range(int *rgb);
int		get_color_rgb(int *color, char **info);
int		get_image(t_vars *info, t_img *img, char *path);
int		save_textures(t_vars *info, char **arr);
int		all_info_read(t_map *map);

/************************[ Movements ]************************/
void	getting_player_position(t_vars *vars);
int		pressing_keys(int keycode, t_vars *vars);
int		key_release(int keycode, t_vars *vars);
void	moving_player(t_vars *vars);

/************************[ RayCasting ]***********************/
t_coor	ft_get_hit_wall(t_vars *vars, t_coor start_pos,
			double angle, int *direction);

/************************[ Rendering ]************************/
int		initializing_images(t_vars *vars);
int		rendering_frames(t_vars *vars);
void	rendering_3d_scenes(t_vars *vars);
void	drawing_floor_and_ceilling(t_vars *vars);

/**************************[ Other ]**************************/
int		exiting_game(t_vars *vars, int exit_status);

#endif
