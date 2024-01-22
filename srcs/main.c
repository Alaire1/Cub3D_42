#include "../includes/cub3d.h"

int	exit_game(t_vars *vars)
{
	exiting_game(vars, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}


void init_map(t_map *map)  //ours
{
	map->ce_color = -1;  
	map->fl_color = -1;  
	map->map = NULL;   
	map->height = 0; //need to add later
	map->width = 0;
	map->start_map_index = 0;
	map->player_count = 0;
	map->north.img = NULL;
	map->south.img = NULL;
	map->west.img = NULL;
	map->east.img = NULL;
}

static void init_mlx(t_mlx *mlx) // ours
{
	mlx->win = NULL;
	mlx->img.img = NULL;
	mlx->fps = 0;
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		print_error("mlx_init() failed");
}

static void init_player(t_player *player) // ours
{
	player->move.x = 0;
	player->move.y = 0;
	player->rotate = 0;
}

static void init_main_struct(t_vars *info) // ours
{
	init_map(&info->map);
	init_mlx(&info->mlx);
	init_player(&info->player);

}
static void	starting_game(t_vars *vars)
{
	vars->mlx.win = mlx_new_window(vars->mlx.mlx, WIDTH, HEIGHT, "cub3d");
	if (!vars->mlx.win)
	{
		printf("Error\nCouldn't open window.\n");
		exiting_game(vars, EXIT_FAILURE);
	}
	mlx_hook(vars->mlx.win, 02, (1L << 0), pressing_keys, vars);
	mlx_hook(vars->mlx.win, 03, (1L << 1), key_release, vars);
	mlx_hook(vars->mlx.win, 17, 0L, exit_game, vars);
	mlx_loop_hook(vars->mlx.mlx, rendering_frames, vars);
	mlx_loop(vars->mlx.mlx);
}

int	main(int argc, char **argv)
{
	t_vars	info;

	check_for_valid_input(argv, argc);
	init_main_struct(&info);
	if (!importing_map(&info, argv[1]))
		exiting_game(&info, EXIT_FAILURE);
	if (!initializing_images(&info))
		exiting_game(&info, EXIT_FAILURE);
	starting_game(&info);
	return (EXIT_SUCCESS);
}
