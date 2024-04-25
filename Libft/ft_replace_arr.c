/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narigi-e <narigi-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:28:43 by narigi-e          #+#    #+#             */
/*   Updated: 2024/01/22 14:28:47 by narigi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_replace_arr(
	char **arr1, char **arr2, unsigned int start, unsigned int size
	)
{
	char	**arr;
	size_t	arr_len;
	t_index	index;

	if (!arr1 || !arr2)
		return (NULL);
	arr_len = ft_arrlen(arr1) - size + ft_arrlen(arr2);
	arr = ft_calloc(arr_len + 1, sizeof(char *));
	if (!arr)
		return (NULL);
	index.i = 0;
	index.j = 0;
	index.k = 0;
	while (index.i < arr_len)
	{
		if (index.i == start)
			index.j += size;
		if (index.i >= start && index.i < start + ft_arrlen(arr2))
			arr[index.i++] = ft_strdup(arr2[index.k++]);
		else
			arr[index.i++] = ft_strdup(arr1[index.j++]);
		if (index.i != 0 && !arr[index.i - 1])
			return (ft_free_2d(arr), NULL);
	}
	return (ft_free_2d(arr1), arr);
}
