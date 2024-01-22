/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narigi-e <narigi-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:26:59 by narigi-e          #+#    #+#             */
/*   Updated: 2024/01/22 14:26:59 by narigi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*buffer;
	size_t		i;

	buffer = s;
	i = 0;
	while (i < n)
	{
		if ((i > 0 && !(unsigned char)buffer[i])
			|| (unsigned char)buffer[i] == (unsigned char)c)
			return ((void *)&buffer[i]);
		i++;
	}
	return (0);
}
