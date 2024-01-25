/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exiting_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraban <akaraban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:43:07 by narigi-e          #+#    #+#             */
/*   Updated: 2024/01/25 12:41:32 by akaraban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	destroying_image(t_main *info, t_img *img)
{
	if (img->img)
		mlx_destroy_image(info->mlx.mlx, img->img);
}

int	exiting_game(t_main *info, int exit_status)
{
	if (info->mlx.win)
		mlx_destroy_window(info->mlx.mlx, info->mlx.win);
	destroying_image(info, &info->mlx.img);
	destroying_image(info, &info->map.north);
	destroying_image(info, &info->map.south);
	destroying_image(info, &info->map.west);
	destroying_image(info, &info->map.east);
	info->map.map = ft_free_2d(info->map.map);
	exit(exit_status);
}
