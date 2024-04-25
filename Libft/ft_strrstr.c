/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narigi-e <narigi-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:34:55 by narigi-e          #+#    #+#             */
/*   Updated: 2024/01/22 14:35:04 by narigi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrstr(const char *haystack, const char *needle)
{
	int	i;
	int	j;

	if (needle[0] == '\0')
		return ((char *)haystack);
	i = ft_strlen(haystack) - 1;
	while (i >= 0)
	{
		j = ft_strlen(needle) - 1;
		while (i - ((int)ft_strlen(needle) - 1 - j) >= 0
			&& haystack[i - ((int)ft_strlen(needle) - 1 - j)] == needle[j])
		{
			if (j == 0)
				return ((char *)&haystack
					[i - ((int)ft_strlen(needle) - 1 - j)]);
			j--;
		}
		i--;
	}
	return (0);
}
