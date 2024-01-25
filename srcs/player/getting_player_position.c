/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getting_player_position.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraban <akaraban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:40:24 by narigi-e          #+#    #+#             */
/*   Updated: 2024/01/25 12:40:37 by akaraban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	getting_player_angle(t_main *info)
{
	int		x;
	int		y;

	x = info->player.pos.x;
	y = info->player.pos.y;
	if (info->map.map[y][x] == 'N')
		info->player.angle = M_PI_2;
	else if (info->map.map[y][x] == 'S')
		info->player.angle = M_PI + M_PI_2;
	else if (info->map.map[y][x] == 'E')
		info->player.angle = M_PI;
	else if (info->map.map[y][x] == 'W')
		info->player.angle = 0;
}

void	getting_player_position(t_main *info)
{
	int	i;
	int	j;

	i = 0;
	while (info->map.map[i])
	{
		j = 0;
		while (info->map.map[i][j])
		{
			if (ft_strchr("NSEW", info->map.map[i][j]))
			{
				info->player.pos.x = (double)j + 0.5;
				info->player.pos.y = (double)i + 0.5;
				getting_player_angle(info);
			}
			j ++;
		}
		i ++;
	}
}
