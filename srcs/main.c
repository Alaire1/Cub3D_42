/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraban <akaraban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:05:53 by narigi-e          #+#    #+#             */
/*   Updated: 2024/01/26 13:21:12 by akaraban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	exit_game(t_main *info)
{
	exiting_game(info, SUCCESS);
	return (SUCCESS);
}

static void	create_window(t_main *info)
{
	info->mlx.win = mlx_new_window(info->mlx.mlx, WIDTH, HEIGHT, NAME);
	if (!info->mlx.win)
	{
		print_error("Couldn't open window.");
		exiting_game(info, ERROR);
	}
}

static void	set_hooks(t_main *info)
{
	mlx_hook(info->mlx.win, 02, (1L << 0), pressing_keys, info);
	mlx_hook(info->mlx.win, 03, (1L << 1), key_release, info);
	mlx_hook(info->mlx.win, 17, 0L, exit_game, info);
	mlx_loop_hook(info->mlx.mlx, rendering_frames, info);
}

static void	start(t_main *info)
{
	create_window(info);
	init_player(&info->player);
	set_hooks(info);
	mlx_loop(info->mlx.mlx);
}

int	main(int argc, char **argv)
{
	t_main	info;

	if (check_for_valid_input(argv, argc))
		return (ERROR);
	init_main_struct(&info);
	if (!importing_map(&info, argv[1]))
		exiting_game(&info, ERROR);
	if (!initializing_images(&info))
		exiting_game(&info, ERROR);
	start(&info);
	return (ERROR);
}
