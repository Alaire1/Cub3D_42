/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narigi-e <narigi-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:22:16 by narigi-e          #+#    #+#             */
/*   Updated: 2024/01/22 14:37:40 by narigi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_arrlen(char **arr)
{
	size_t	arrlen;

	arrlen = 0;
	while (arr[arrlen])
		arrlen++;
	return (arrlen);
}
