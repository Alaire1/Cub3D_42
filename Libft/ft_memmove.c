/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narigi-e <narigi-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:27:30 by narigi-e          #+#    #+#             */
/*   Updated: 2024/01/22 14:27:30 by narigi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*dest;
	const char	*source;

	if (!dst && !src)
		return (NULL);
	if (dst < src)
	{
		source = src;
		dest = dst;
		while (len--)
			*dest++ = *source++;
	}
	else
	{
		source = src + len - 1;
		dest = dst + len - 1;
		while (len--)
			*dest-- = *source--;
	}
	return (dst);
}
