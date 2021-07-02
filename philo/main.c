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
	print_it(philo, LEFT_FORK);
	pthread_mutex_lock(&philo->arg->forks[right]);
	print_it(philo, RIGHT_FORK);
	print_it(philo, EAT);
	philo->last_eat = get_time();
	philo->eat_counter++;
	philo->state = EAT;
	usleep(philo->arg->time_toeat * 1000 - 14000);
	while (get_time() - philo->last_eat < philo->arg->time_toeat)
		;
}

void	check_count(t_philo *philo, int i, t_arg *arg)
{
	if (philo[i].eat_counter == arg->must_eat)
	{
		philo[i].state = SLEEP;
		arg->all_eat++;
	}
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
					print_it(philo, DEAD);
					return ;
				}
			}
			check_count(philo, i, arg);
			if (arg->all_eat == arg->number)
			{
				i = -1;
				while (++i < arg->number)
					pthread_join(philo[i].t, NULL);
				return ;
			}
			i++;
		}
		usleep(10);
	}
}

int	main(int ac, char **av)
{
	t_philo	*philo;
	t_arg	arg;
	int		i;

	if (ac < 5 || ac > 6)
		return (fail("error arguments number\n"));
	if (!(check_args(av)))
		return (fail("error arguments\n"));
	arg.number = 0;
	get_args(&arg, av, ac, &philo);
	if (arg.number == 0)
		return (0);
	init_philo(philo, &arg);
	i = -1;
	while (++i < arg.number)
	{
		pthread_create(&philo[i].t, NULL, philo_funcn, &philo[i]);
		usleep(100);
	}
	check_eat_death(philo, &arg);
	usleep(100);
	free(philo);
	return (0);
}
