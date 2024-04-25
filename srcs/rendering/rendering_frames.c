/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_frames.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraban <akaraban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:42:35 by narigi-e          #+#    #+#             */
/*   Updated: 2024/01/25 15:38:13 by akaraban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	initializing_images(t_main *info)
{
	info->mlx.img.img = mlx_new_image(info->mlx.mlx, WIDTH, HEIGHT);
	if (!info->mlx.img.img)
		return (print_error("Couldn't create images."), 0);
	info->mlx.img.data = (int *)mlx_get_data_addr(info->mlx.img.img,
			&info->mlx.img.bpp, &info->mlx.img.line_len,
			&info->mlx.img.endian);
	return (1);
}

static void	counting_fps(t_main *info)
{
	static long	prev_timestamp;
	static long	counter;
	static int	frames;

	if (!prev_timestamp)
		prev_timestamp = getting_current_time();
	info->mlx.fspeed = (getting_current_time() - prev_timestamp) / 1000.0;
	prev_timestamp = getting_current_time();
	if (!counter)
		counter = getting_current_time() + 1000;
	if (counter <= getting_current_time())
	{
		counter = getting_current_time() + 1000;
		info->mlx.fps = frames;
		frames = 0;
	}
	frames ++;
}

int	rendering_frames(t_main *info)
{
	counting_fps(info);
	moving_player(info);
	rendering_3d_scenes(info);
	mlx_put_image_to_window(info->mlx.mlx, info->mlx.win,
		info->mlx.img.img, 0, 0);
	return (1);
}
