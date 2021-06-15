/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anassif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 12:31:51 by anassif           #+#    #+#             */
/*   Updated: 2019/10/14 12:31:53 by anassif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	count_numbers(int n)
{
	int i;

	i = 0;
	if (n < 0)
	{
		i = 1;
		n = -n;
	}
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char		*ft_itoa(int n)
{
	char			*str;
	int				c;
	unsigned int	nbr;

	nbr = 0;
	c = count_numbers(n);
	str = malloc(sizeof(char) * (c + 1));
	if (str == NULL)
		return (NULL);
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		str[0] = '-';
		nbr = -n;
	}
	else
		nbr = n;
	str[c] = '\0';
	while (nbr > 0)
	{
		str[c-- - 1] = nbr % 10 + '0';
		nbr = nbr / 10;
	}
	return (str);
}
