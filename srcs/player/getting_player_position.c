/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getting_player_position.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narigi-e <narigi-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:40:24 by narigi-e          #+#    #+#             */
/*   Updated: 2024/01/22 12:40:30 by narigi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	getting_player_angle(t_vars *vars)
{
	int		x;
	int		y;

	x = vars->player.pos.x;
	y = vars->player.pos.y;
	if (vars->map.map[y][x] == 'N')
		vars->player.angle = M_PI_2;
	else if (vars->map.map[y][x] == 'S')
		vars->player.angle = M_PI + M_PI_2;
	else if (vars->map.map[y][x] == 'E')
		vars->player.angle = M_PI;
	else if (vars->map.map[y][x] == 'W')
		vars->player.angle = 0;
}

void	getting_player_position(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (vars->map.map[i])
	{
		j = 0;
		while (vars->map.map[i][j])
		{
			if (ft_strchr("NSEW", vars->map.map[i][j]))
			{
				vars->player.pos.x = (double)j + 0.5;
				vars->player.pos.y = (double)i + 0.5;
				getting_player_angle(vars);
			}
			j ++;
		}
		i ++;
	}
}
