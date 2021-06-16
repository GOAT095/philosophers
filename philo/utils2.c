/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anassif <anassif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 21:49:21 by anassif           #+#    #+#             */
/*   Updated: 2021/06/16 15:15:18 by anassif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(char **av)
{
	int	j;
	int	i;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!(av[i][j] <= '9' && av[i][j] >= '0'))
				return (0);
			j++;
		}
		if ((ft_atoi(av[i])) < 0)
			return (0);
		i++;
	}
	return (1);
}

void	init_philo(t_philo *philo, t_arg *arg)
{
	int	i;

	i = -1;
	while (++i < arg->number)
	{
		philo[i].id = i;
		philo[i].last_eat = get_time();
		philo[i].eat_counter = 0;
		philo[i].arg = arg;
		philo[i].state = START;
	}
}
