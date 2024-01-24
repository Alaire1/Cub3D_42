/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraban <akaraban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:40:38 by narigi-e          #+#    #+#             */
/*   Updated: 2024/01/24 16:29:32 by akaraban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	getting_player_direction(t_main *vars)
{
	double	direction_angle;

	if (vars->player.rotate)
		vars->player.angle = radian_calculations(vars->player.angle,
				vars->player.rotate * vars->mlx.fspeed * ROT_SPEED);
	direction_angle = vars->player.angle;
	if (vars->player.move.y == -1)
		direction_angle = radian_calculations(direction_angle, M_PI);
	else if (vars->player.move.x)
		direction_angle = radian_calculations(direction_angle,
				-vars->player.move.x * M_PI_2);
	if (vars->player.move.x && vars->player.move.y)
		direction_angle = radian_calculations(direction_angle,
				vars->player.move.x * M_PI_4);
	vars->player.dir.x = cos(direction_angle);
	vars->player.dir.y = sin(direction_angle);
}

void	moving_player(t_main *vars)
{
	t_coor	new_pos;

	getting_player_direction(vars);
	if (!(int)vars->player.move.x && !(int)vars->player.move.y)
		return ;
	new_pos.x = vars->player.pos.x
		+ (vars->player.dir.x * vars->mlx.fspeed * SPEED);
	if (vars->map.map[(int)vars->player.pos.y][(int)new_pos.x] != '1')
		vars->player.pos.x = new_pos.x;
	new_pos.y = vars->player.pos.y
		+ (vars->player.dir.y * vars->mlx.fspeed * SPEED);
	if (vars->map.map[(int)new_pos.y][(int)vars->player.pos.x] != '1')
		vars->player.pos.y = new_pos.y;
}

int	pressing_keys(int keycode, t_main *vars)
{
	if (keycode == KEY_A)
		vars->player.move.x = -1;
	else if (keycode == KEY_W || keycode == KEY_UP)
		vars->player.move.y = -1;
	else if (keycode == KEY_D)
		vars->player.move.x = 1;
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		vars->player.move.y = 1;
	else if (keycode == KEY_LEFT)
		vars->player.rotate = -1;
	else if (keycode == KEY_RIGHT)
		vars->player.rotate = 1;
	else if (keycode == KEY_ESC)
		exiting_game(vars, EXIT_SUCCESS);
	return (0);
}

int	key_release(int keycode, t_main *vars)
{
	if (keycode == KEY_A)
		vars->player.move.x = 0;
	else if (keycode == KEY_W || keycode == KEY_UP)
		vars->player.move.y = 0;
	else if (keycode == KEY_D)
		vars->player.move.x = 0;
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		vars->player.move.y = 0;
	else if (keycode == KEY_LEFT)
		vars->player.rotate = 0;
	else if (keycode == KEY_RIGHT)
		vars->player.rotate = 0;
	return (0);
}
