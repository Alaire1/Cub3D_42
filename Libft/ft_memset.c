/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narigi-e <narigi-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:27:38 by narigi-e          #+#    #+#             */
/*   Updated: 2024/01/22 14:27:38 by narigi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*buffer;
	size_t			i;

	buffer = b;
	i = 0;
	while (i < len)
	{
		buffer[i] = (unsigned char)c;
		i++;
	}
	return (buffer);
}
