/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraban <akaraban.student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:40:38 by narigi-e          #+#    #+#             */
/*   Updated: 2024/04/23 21:15:37 by akaraban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	getting_player_direction(t_main *info)
{
	double	direction_angle;

	if (info->player.rotate)
		info->player.angle = radian_calculations(info->player.angle,
				info->player.rotate * info->mlx.fspeed * ROT_SPEED);
	direction_angle = info->player.angle;
	if (info->player.move.y == -1)
		direction_angle = radian_calculations(direction_angle, M_PI);
	else if (info->player.move.x)
		direction_angle = radian_calculations(direction_angle,
				-info->player.move.x * M_PI_2);
	if (info->player.move.x && info->player.move.y)
		direction_angle = radian_calculations(direction_angle,
				info->player.move.x * M_PI_4);
	info->player.dir.x = cos(direction_angle);
	info->player.dir.y = sin(direction_angle);
}

void	moving_player(t_main *info)
{
	t_coor	new_pos;

	getting_player_direction(info);
	if (!(int)info->player.move.x && !(int)info->player.move.y)
		return ;
	new_pos.x = info->player.pos.x
		+ (info->player.dir.x * info->mlx.fspeed * SPEED);
	if (info->map.map[(int)info->player.pos.y][(int)new_pos.x] != '1')
		info->player.pos.x = new_pos.x;
	new_pos.y = info->player.pos.y
		+ (info->player.dir.y * info->mlx.fspeed * SPEED);
	if (info->map.map[(int)new_pos.y][(int)info->player.pos.x] != '1')
		info->player.pos.y = new_pos.y;
}

int	pressing_keys(int keycode, t_main *info)
{
	if (keycode == KEY_A)
		info->player.move.x = -1;
	else if (keycode == KEY_W || keycode == KEY_UP)
		info->player.move.y = -1;
	else if (keycode == KEY_D)
		info->player.move.x = 1;
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		info->player.move.y = 1;
	else if (keycode == KEY_LEFT)
		info->player.rotate = -1;
	else if (keycode == KEY_RIGHT)
		info->player.rotate = 1;
	else if (keycode == KEY_ESC)
		exiting_game(info, EXIT_SUCCESS);
	return (0);
}

int	key_release(int keycode, t_main *info)
{
	if (keycode == KEY_A)
		info->player.move.x = 0;
	else if (keycode == KEY_W || keycode == KEY_UP)
		info->player.move.y = 0;
	else if (keycode == KEY_D)
		info->player.move.x = 0;
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		info->player.move.y = 0;
	else if (keycode == KEY_LEFT)
		info->player.rotate = 0;
	else if (keycode == KEY_RIGHT)
		info->player.rotate = 0;
	return (0);
}
