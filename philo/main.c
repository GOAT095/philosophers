/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anassif <anassif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 16:05:34 by anassif           #+#    #+#             */
/*   Updated: 2021/06/15 21:29:10 by anassif          ###   ########.fr       */
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

void	*philo_funcn(void *data)
{
	t_philo				*philo;
	unsigned long long	start_sleep;
	int					right;

	philo = data;
	while (philo->eat_counter < philo->arg->must_eat
		|| philo->arg->must_eat == -1)
	{
		right = (philo->id + 1) % philo->arg->number;
		printf("\033[0;32mphilo %d is thinking\n", philo->id + 1);
		pthread_mutex_lock(&philo->arg->forks[philo->id]);
		printf("\033[0;31mphilo %d has taken left fork\n", philo->id + 1);
		pthread_mutex_lock(&philo->arg->forks[right]);
		printf("\033[0;31mphilo %d has taken right fork\n", philo->id + 1);
		printf("\033[0;32mphilo %d is eating\n", philo->id + 1);
		philo->last_eat = get_time();
		philo->eat_counter++;
		philo->state = EAT;
		usleep(philo->arg->time_toeat * 1000 - 14000);
		while (get_time() - philo->last_eat < philo->arg->time_toeat)
			;
		printf("\033[0;32mphilo %d is sleeping\n", philo->id + 1);
		pthread_mutex_unlock(&philo->arg->forks[right]);
		pthread_mutex_unlock(&philo->arg->forks[philo->id]);
		start_sleep = get_time();
		philo->state = SLEEP;
		usleep(philo->arg->time_tosleep * 1000 - 1400);
		while (get_time() - start_sleep < philo->arg->time_tosleep)
			;
	}
	return (NULL);
}

void	check_eat_death(t_philo *philo, t_arg *arg)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < arg->number)
		{
			if (philo[i].state != EAT
				&& ((get_time() - philo[i].last_eat) >= arg->time_todie))
			{
				philo[i].state = DEAD;
				printf("\033[0;37mphilo %d is dead\n", philo[i].id + 1);
				return ;
			}
			if (philo[i].eat_counter == arg->must_eat)
			{
				philo[i].state = SLEEP;
				arg->all_eat++;
			}
			if (arg->all_eat == arg->number)
			{	
				i = -1;
				while (++i < arg->number)
					pthread_join(philo[i].t, NULL);
				return ;
			}
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
	init_philo(philo, &arg);
	i = -1;
	while (++i < arg.number)
	{
		pthread_create(&philo[i].t, NULL, philo_funcn, &philo[i]);
		usleep(100);
	}
	check_eat_death(philo, &arg);
	return (0);
}
