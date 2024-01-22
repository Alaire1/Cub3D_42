/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getting_distances.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narigi-e <narigi-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:43:16 by narigi-e          #+#    #+#             */
/*   Updated: 2024/01/22 12:43:18 by narigi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

double	getting_distance(t_coor point1, t_coor point2)
{
	t_coor	dist;

	dist.x = powf(point2.x - point1.x, 2);
	dist.y = powf(point2.y - point1.y, 2);
	return (sqrtf(dist.x + dist.y));
}
