/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_frames.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narigi-e <narigi-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:42:35 by narigi-e          #+#    #+#             */
/*   Updated: 2024/01/22 13:00:37 by narigi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	initializing_images(t_vars *vars)
{
	vars->mlx.img.img = mlx_new_image(vars->mlx.mlx, WIDTH, HEIGHT);
	if (!vars->mlx.img.img)
		return (printf("Error\nCouldn't create images.\n"), 0);
	vars->mlx.img.data = (int *)mlx_get_data_addr(vars->mlx.img.img,
			&vars->mlx.img.bpp, &vars->mlx.img.line_len,
			&vars->mlx.img.endian);
	return (1);
}

static void	counting_fps(t_vars *vars)
{
	static long	prev_timestamp;
	static long	counter;
	static int	frames;

	if (!prev_timestamp)
		prev_timestamp = getting_current_time();
	vars->mlx.fspeed = (getting_current_time() - prev_timestamp) / 1000.0;
	prev_timestamp = getting_current_time();
	if (!counter)
		counter = getting_current_time() + 1000;
	if (counter <= getting_current_time())
	{
		counter = getting_current_time() + 1000;
		vars->mlx.fps = frames;
		frames = 0;
	}
	frames ++;
}

int	rendering_frames(t_vars *vars)
{
	counting_fps(vars);
	moving_player(vars);
	rendering_3d_scenes(vars);
	mlx_put_image_to_window(vars->mlx.mlx, vars->mlx.win,
		vars->mlx.img.img, 0, 0);
	return (1);
}
