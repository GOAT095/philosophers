/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anassif <anassif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 16:05:34 by anassif           #+#    #+#             */
/*   Updated: 2021/06/28 15:15:37 by anassif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo, int right)
{
	pthread_mutex_lock(&philo->arg->forks[philo->id]);
	print_it(philo, LEFT_FORK, 0);
	pthread_mutex_lock(&philo->arg->forks[right]);
	print_it(philo, RIGHT_FORK, 0);
	print_it(philo, EAT, 0);
	philo->last_eat = get_time();
	philo->eat_counter++;
	philo->state = EAT;
	usleep(philo->arg->time_toeat * 1000 - 14000);
	while (get_time() - philo->last_eat < philo->arg->time_toeat)
		;
}

void	check_eat_death(t_philo *philo, t_arg *arg)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < arg->number)
		{
			if (philo[i].state != EAT)
			{
				if ((get_time() - philo[i].last_eat) >= arg->time_todie)
				{
					print_it(philo, DEAD, i);
					return ;
				}
				if (arg->must_eat != -1)
				{
					if (philo[i].eat_counter >= arg->must_eat)
						arg->all_eat++;
					if (arg->all_eat >= arg->number)
					{
						i = -1;
						while (++i < arg->number)
							pthread_join(philo[i].t, NULL);
						return ;
					}
				}
			}
			i++;
		}
		usleep(10);
	}
}

int	main(int ac, char **av)
{
	t_philo	*philo;
	t_arg	*arg;
	int		i;

	g_time = get_time();
	if (ac < 5 || ac > 6)
		return (fail("error arguments number\n"));
	if (!(check_args(av)))
		return (fail("error arguments\n"));
	arg = (t_arg *)malloc(sizeof(t_arg));
	arg->number = 0;
	
	get_args(arg, av, ac, &philo);
	if (arg->number == 0)
		return (0);
	init_philo(philo, arg);
	i = -1;
	while (++i < arg->number)
	{
		philo[i].last_eat = get_time();
		pthread_create(&philo[i].t, NULL, philo_funcn, &philo[i]);
		usleep(100);
	}
	check_eat_death(philo, arg);
	usleep(100);
	free(philo);
	free(arg);
	return (0);
}
