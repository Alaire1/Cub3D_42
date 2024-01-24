/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraban <akaraban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:51:26 by narigi-e          #+#    #+#             */
/*   Updated: 2024/01/24 20:04:29 by akaraban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	array_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

int	ft_isnumber2(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i ++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i ++;
	}
	return (1);
}

int	trgb_to_int(int t, int red, int green, int blue)
{
	return (((t & 0xFF) << 24) | ((red & 0xFF) << 16)
		| ((green & 0xFF) << 8) | (blue & 0xFF));
}

int	validate_rgb_values(char **arr)
{
	if (!ft_isnumber2(arr[0]) || !ft_isnumber2(arr[1]) || !ft_isnumber2(arr[2]))
	{
		print_error("Invalid RGB values.");
		ft_free_array(arr);
		return (0);
	}
	return (1);
}
