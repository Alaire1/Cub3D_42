/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radian_calculations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narigi-e <narigi-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:43:25 by narigi-e          #+#    #+#             */
/*   Updated: 2024/01/22 12:43:29 by narigi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

double	radian_calculations(double radian, double amout)
{
	radian += amout;
	while (radian > 2 * M_PI)
		radian -= 2 * M_PI;
	while (radian < 0)
		radian += 2 * M_PI;
	return (radian);
}

double	radian_to_degree(double radian)
{
	return (radian * (180.0 / M_PI));
}

double	degree_to_radian(double degree)
{
	return (degree * (M_PI / 180.0));
}
