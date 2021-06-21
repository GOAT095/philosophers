/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anassif <anassif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 16:05:34 by anassif           #+#    #+#             */
/*   Updated: 2021/06/17 17:36:48 by anassif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo, int right)
{
	printf("%llu %d is thinking\n",
		get_time() - philo->arg->program_start, philo->id + 1);
	sem_wait(&philo->arg->forks[philo->id]);
	printf("%llu %d has taken a fork\n",
		get_time() - philo->arg->program_start, philo->id + 1);
	sem_wait(&philo->arg->forks[right]);
	printf("%llu %d has taken a fork\n",
		get_time() - philo->arg->program_start, philo->id + 1);
	printf("%llu %d is eating\n",
		get_time() - philo->arg->program_start, philo->id + 1);
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
		if (philo[i].state != EAT
			&& ((get_time() - philo.last_eat) >= arg->time_todie))
		{
			printf("%llu %d is dead\n",
				get_time() - philo->arg->program_start, philo.id + 1);
			return ;
		}
		check_count(philo, i, arg);
		if (arg->all_eat == arg->number)
		{
			i = -1;
			while (++i < arg->number)
				pthread_join(philo.t, NULL);
			return ;
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
		if (fork() == 0)
		{
			pthread_create(&philo[i].t, NULL, philo_funcn, &philo[i]);
			check_eat_death(philo[i], arg);
		}
		
		usleep(100);
	}
	return (0);
}
