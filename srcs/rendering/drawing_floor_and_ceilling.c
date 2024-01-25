/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_floor_and_ceilling.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraban <akaraban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:41:12 by narigi-e          #+#    #+#             */
/*   Updated: 2024/01/25 12:40:54 by akaraban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	drawing_floor_and_ceilling(t_main *info)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				info->mlx.img.data[y * WIDTH + x] = info->map.ce_color;
			else
				info->mlx.img.data[y * WIDTH + x] = info->map.fl_color;
			x ++;
		}
		y ++;
	}
}
