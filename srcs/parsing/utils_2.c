/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraban <akaraban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:26:46 by akaraban          #+#    #+#             */
/*   Updated: 2024/01/24 16:55:48 by akaraban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	only_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int	empty_line(char *line)
{
	if (ft_strcmp(line, "\n") == 0)
		return (1);
	else if (ft_strcmp(line, "") == 0)
		return (1);
	else if (only_spaces(line))
		return (1);
	return (0);
}
