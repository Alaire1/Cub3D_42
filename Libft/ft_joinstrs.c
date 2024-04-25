/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joinstrs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narigi-e <narigi-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:26:22 by narigi-e          #+#    #+#             */
/*   Updated: 2024/01/22 14:38:35 by narigi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_joinstrs(char **array, char c)
{
	char	*str;
	size_t	i;

	str = ft_strdup("");
	if (!str)
		return (NULL);
	i = 0;
	while (array[i])
	{
		str = ft_stradd(str, array[i]);
		if (!str)
			return (ft_free(str), NULL);
		if (array[i + 1])
		{
			str = ft_stradd(str, &c);
			if (!str)
				return (ft_free(str), NULL);
		}
		i++;
	}
	return (str);
}
