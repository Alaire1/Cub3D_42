/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exiting_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narigi-e <narigi-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:43:07 by narigi-e          #+#    #+#             */
/*   Updated: 2024/01/22 12:43:09 by narigi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	destroying_image(t_vars *vars, t_img *img)
{
	if (img->img)
		mlx_destroy_image(vars->mlx.mlx, img->img);
}

int	exiting_game(t_vars *vars, int exit_status)
{
	if (vars->mlx.win)
		mlx_destroy_window(vars->mlx.mlx, vars->mlx.win);
	destroying_image(vars, &vars->mlx.img);
	destroying_image(vars, &vars->map.north);
	destroying_image(vars, &vars->map.south);
	destroying_image(vars, &vars->map.west);
	destroying_image(vars, &vars->map.east);
	vars->map.map = ft_free_2d(vars->map.map);
	exit(exit_status);
}
