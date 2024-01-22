/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_floor_and_ceilling.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narigi-e <narigi-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:41:12 by narigi-e          #+#    #+#             */
/*   Updated: 2024/01/22 12:41:16 by narigi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	drawing_floor_and_ceilling(t_vars *vars)
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
				vars->mlx.img.data[y * WIDTH + x] = vars->map.ce_color;
			else
				vars->mlx.img.data[y * WIDTH + x] = vars->map.fl_color;
			x ++;
		}
		y ++;
	}
}
