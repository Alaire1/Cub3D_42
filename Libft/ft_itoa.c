/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narigi-e <narigi-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:26:12 by narigi-e          #+#    #+#             */
/*   Updated: 2024/01/22 14:38:29 by narigi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(int n, int count_zero)
{
	int		intlen;

	intlen = 0;
	if (count_zero && n == 0)
		return (1);
	while (n != 0)
	{
		intlen++;
		n /= 10;
	}
	return (intlen);
}

char	*ft_itoa(int n)
{
	char	*integer;
	long	nb;
	int		isnegative;

	nb = n;
	isnegative = 0;
	if (nb < 0)
	{
		isnegative = 1;
		nb = -nb;
	}
	integer = (char *) malloc (ft_intlen(nb, 1) + isnegative + 1);
	if (integer == NULL)
		return (0);
	integer[ft_intlen(nb, 1) + isnegative] = '\0';
	if (nb == 0)
		integer[0] = '0';
	while (ft_intlen(nb, 0) > 0)
	{
		integer[ft_intlen(nb, 0) - 1 + isnegative] = (nb % 10) + '0';
		nb /= 10;
	}
	if (isnegative)
		integer[0] = '-';
	return (integer);
}
