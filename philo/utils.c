/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anassif <anassif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 19:56:36 by anassif           #+#    #+#             */
/*   Updated: 2021/06/15 20:02:47 by anassif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo1.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	long long	n;
	int			sign;
	int			i;

	i = 0;
	sign = 1;
	n = 0;
	while (str[i] != '\0' && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10;
		n = n + str[i] - '0';
		i++;
	}
	if (n < 0 && sign > 0)
		return (-1);
	if (n < 0 && sign < 0)
		return (0);
	return (n * sign);
}

int	fail(char *str)
{
	write(1, str, ft_strlen(str));
	return (1);
}
