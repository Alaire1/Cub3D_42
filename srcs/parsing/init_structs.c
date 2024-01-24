/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraban <akaraban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:42:35 by narigi-e          #+#    #+#             */
/*   Updated: 2024/01/24 19:53:19 by akaraban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	init_map(t_map *map)
{
	map->ce_color = -1;
	map->fl_color = -1;
	map->map = NULL;
	map->height = 0;
	map->width = 0;
	map->start_map_index = 0;
	map->player_count = 0;
	map->north.img = NULL;
	map->south.img = NULL;
	map->west.img = NULL;
	map->east.img = NULL;
}

static void	init_mlx(t_mlx *mlx)
{
	mlx->win = NULL;
	mlx->img.img = NULL;
	mlx->fps = 0;
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		print_error("mlx_init() failed");
}

void	init_player(t_player *player)
{
	player->move.x = 0;
	player->move.y = 0;
	player->rotate = 0;
}

void	init_main_struct(t_main *info)
{
	init_map(&info->map);
	init_mlx(&info->mlx);
}
