/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_3d_scenes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraban <akaraban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:41:36 by narigi-e          #+#    #+#             */
/*   Updated: 2024/01/26 15:53:15 by akaraban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// #define RADIAN_INC	0.06

static int	getting_texture_pixel(t_img img, t_render *render, int ty)
{
	int		tx;
	double	ty_step;
	double	ty_off;

	if (render->direc == 'h')
		tx = img.width * (render->hit_wall.x - (int)render->hit_wall.x);
	else
		tx = img.width * (render->hit_wall.y - (int)render->hit_wall.y);
	ty_step = img.height / render->wall_orig_height;
	ty_off = 0;
	if (render->wall_orig_height > HEIGHT)
		ty_off = (render->wall_orig_height - HEIGHT) / 2;
	ty = ty_off * ty_step + (ty * ty_step);
	return (img.data[abs(ty) * img.width + abs(tx)]);
}

static void	drawing_pixel(t_main *info, t_render *render, int *data, int ty)
{
	t_img	*img;
	int		color;

	if (render->direc == 'h' && render->angle < M_PI)
		img = &info->map.north;
	else if (render->direc == 'h' && render->angle < 2 * M_PI)
		img = &info->map.south;
	else if (render->direc == 'v'
		&& (render->angle < M_PI_2 || render->angle > M_PI + M_PI_2))
		img = &info->map.west;
	else
		img = &info->map.east;
	color = getting_texture_pixel(*img, render, ty);
	if (color != trgb_to_int(255, 0, 0, 0))
		*data = color;
}

static void	drawing_walls(t_main *info, t_render *render)
{
	int	x;
	int	y;
	int	ty;

	ty = 0;
	y = (HEIGHT / 2) - (render->wall_dim.height / 2);
	while (y < (HEIGHT / 2) - (render->wall_dim.height / 2)
		+ render->wall_dim.height && y < HEIGHT)
	{
		x = (render->degree / RADIAN_INC) * render->wall_dim.width;
		while (x < ((render->degree / RADIAN_INC) * render->wall_dim.width)
			+ render->wall_dim.width && x < WIDTH)
		{
			drawing_pixel(info, render,
				&info->mlx.img.data[y * WIDTH + x], ty - 1);
			x ++;
		}
		ty ++;
		y ++;
	}
}

static void	getting_walls_dimensions(t_main *info, t_render *render,
	t_coor start_pos, double degree)
{
	render->degree = degree;
	render->hit_wall = ft_get_hit_wall(info, start_pos,
			render->angle, &render->direc);
	render->dist = getting_distance(info->player.pos, render->hit_wall)
		* cos(radian_calculations(info->player.angle, -render->angle));
	render->wall_dim.width = WIDTH / (FOV / RADIAN_INC);
	render->wall_dim.height = HEIGHT;
	if (render->dist > 0)
		render->wall_dim.height = HEIGHT / render->dist;
	render->wall_orig_height = render->wall_dim.height;
	if (render->wall_dim.height > HEIGHT)
		render->wall_dim.height = HEIGHT;
}

void	rendering_3d_scenes(t_main *info)
{
	t_render	render;
	double		degree;

	drawing_floor_and_ceilling(info);
	degree = 0;
	while (degree <= FOV)
	{
		render.angle = radian_calculations(info->player.angle,
				degree_to_radian(degree - (FOV / 2)));
		getting_walls_dimensions(info, &render, info->player.pos, degree);
		drawing_walls(info, &render);
		degree += RADIAN_INC;
	}
}
