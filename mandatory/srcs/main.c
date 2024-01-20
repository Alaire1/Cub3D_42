/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraban <akaraban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 11:49:49 by hel-makh          #+#    #+#             */
/*   Updated: 2024/01/20 15:27:13 by akaraban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	exit_game(t_vars *vars)
{
	ft_exit_game(vars, EXIT_SUCCESS);
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

static void init_main_struct(t_vars *info) // ours
{
	init_map(&info->map);
	init_mlx(&info->mlx);

}
static void	ft_start_game(t_vars *vars)
{
	vars->mlx.win = mlx_new_window(vars->mlx.mlx, WIDTH, HEIGHT, "cub3d");
	if (!vars->mlx.win)
	{
		printf("Error\nCouldn't open window.\n");
		ft_exit_game(vars, EXIT_FAILURE);
	}
	vars->player.move.x = 0;
	vars->player.move.y = 0;
	vars->player.rotate = 0;
	mlx_hook(vars->mlx.win, 02, (1L << 0), key_press, vars);
	mlx_hook(vars->mlx.win, 03, (1L << 1), key_release, vars);
	mlx_hook(vars->mlx.win, 17, 0L, exit_game, vars);
	mlx_loop_hook(vars->mlx.mlx, frame_rendering, vars);
	mlx_loop(vars->mlx.mlx);
}

int	main(int argc, char **argv)
{
	t_vars	info;

	check_for_valid_input(argv, argc);
	init_main_struct(&info);
	if (!ft_import_map(&info, argv[1]))
		ft_exit_game(&info, EXIT_FAILURE);
	if (!ft_init_images(&info))
		ft_exit_game(&info, EXIT_FAILURE);
	ft_start_game(&info);
	return (EXIT_SUCCESS);
}
