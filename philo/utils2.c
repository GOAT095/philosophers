/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anassif <anassif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 21:49:21 by anassif           #+#    #+#             */
/*   Updated: 2021/06/28 15:27:35 by anassif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_it(t_philo *philo, int i, int x)
{
	x = 0;
	pthread_mutex_lock(&(philo->arg->protect_output));
	// printf("adress == /%p/\n", &(philo->arg->protect_output));
	if (i == THINKING)
		printf("%llu %d is thinking\n",
			get_time() - philo->arg->program_start, philo->id + 1);
	else if (i == EAT)
		printf("%llu %d is eating\n",
			get_time() - philo->arg->program_start, philo->id + 1);
	else if (i == LEFT_FORK || i == RIGHT_FORK)
		printf("%llu %d has taken a fork\n",
			get_time() - philo->arg->program_start, philo->id + 1);
	else if (i == SLEEP)
		printf("%llu %d is sleeping\n",
			get_time() - philo->arg->program_start, philo->id + 1);
	
	else if (i == DEAD)
	{
		printf("%llu %d is dead\n",
			get_time() - philo->arg->program_start, philo->id + 1);
		return ;
	}
	// printf("adress == /%p/\n", &(philo->arg->protect_output));
	pthread_mutex_unlock(&(philo->arg->protect_output));
}

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
	while ((philo->eat_counter < philo->arg->must_eat
		|| philo->arg->must_eat == -1) && philo->arg->dead == 0)
	{
		right = (philo->id + 1) % philo->arg->number;
		eating(philo, right);
		if (!philo->arg->dead)
			print_it(philo, SLEEP, 0);
		pthread_mutex_unlock(&philo->arg->forks[philo->id]);
		pthread_mutex_unlock(&philo->arg->forks[right]);
		start_sleep = get_time();
		philo->state = SLEEP;
		usleep(philo->arg->time_tosleep * 1000 - 1400);
		while (get_time() - start_sleep < philo->arg->time_tosleep)
			;
		print_it(philo, THINKING, 0);
	}
	return (NULL);
}
