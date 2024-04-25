/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narigi-e <narigi-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:31:43 by narigi-e          #+#    #+#             */
/*   Updated: 2024/01/22 14:31:46 by narigi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*buffer;

	if (!s1)
		return (0);
	buffer = (char *) malloc (ft_strlen(s1) + ft_strlen(s2) + 1);
	if (buffer == NULL)
		return (0);
	ft_strcpy(buffer, s1);
	ft_strcat(buffer, s2);
	return (buffer);
}
