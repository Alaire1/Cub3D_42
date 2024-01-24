/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraban <akaraban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:05:53 by narigi-e          #+#    #+#             */
/*   Updated: 2024/01/24 16:40:58 by akaraban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	exit_game(t_main *vars)
{
	exiting_game(vars, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

static void	start(t_main *vars)
{
	vars->mlx.win = mlx_new_window(vars->mlx.mlx, WIDTH, HEIGHT, "cub3d");
	if (!vars->mlx.win)
	{
		printf("Error\nCouldn't open window.\n");
		exiting_game(vars, EXIT_FAILURE);
	}
	init_player(&vars->player);
	mlx_hook(vars->mlx.win, 02, (1L << 0), pressing_keys, vars);
	mlx_hook(vars->mlx.win, 03, (1L << 1), key_release, vars);
	mlx_hook(vars->mlx.win, 17, 0L, exit_game, vars);
	mlx_loop_hook(vars->mlx.mlx, rendering_frames, vars);
	mlx_loop(vars->mlx.mlx);
}

int	main(int argc, char **argv)
{
	t_main	info;

	check_for_valid_input(argv, argc);
	init_main_struct(&info);
	if (!importing_map(&info, argv[1]))
		exiting_game(&info, EXIT_FAILURE);
	if (!initializing_images(&info))
		exiting_game(&info, EXIT_FAILURE);
	start(&info);
	return (EXIT_SUCCESS);
}
