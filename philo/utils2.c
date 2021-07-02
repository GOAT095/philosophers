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

void	print_it2(t_philo *philo, int i)
{
	if (i == EAT)
	{
		ft_putnbr_fd(get_time() - philo->arg->program_start, 1);
		ft_putstr_fd(" ", 1);
		ft_putnbr_fd(philo->id + 1, 1);
		ft_putstr_fd(" is eating\n", 1);
	}
	else if (i == LEFT_FORK || i == RIGHT_FORK)
	{
		ft_putnbr_fd(get_time() - philo->arg->program_start, 1);
		ft_putstr_fd(" ", 1);
		ft_putnbr_fd(philo->id + 1, 1);
		ft_putstr_fd(" has taken a fork\n", 1);
	}
}

void	print_it(t_philo *philo, int i, int index)
{
	pthread_mutex_lock(&philo->arg->protect_output);
	print_it2(philo, i);
	if (i == THINKING)
	{
		ft_putnbr_fd(get_time() - philo->arg->program_start, 1);
		ft_putstr_fd(" ", 1);
		ft_putnbr_fd(philo->id + 1, 1);
		ft_putstr_fd(" is thinking\n", 1);
	}
	else if (i == SLEEP)
	{	
		ft_putnbr_fd(get_time() - philo->arg->program_start, 1);
		ft_putstr_fd(" ", 1);
		ft_putnbr_fd(philo->id + 1, 1);
		ft_putstr_fd(" is sleeping\n", 1);
	}
	else if (i == DEAD)
	{
		ft_putnbr_fd(get_time() - philo->arg->program_start, 1);
		ft_putstr_fd(" ", 1);
		ft_putnbr_fd(philo[index].id + 1, 1);
		ft_putstr_fd(" is dead\n", 1);
		return ;
	}
	pthread_mutex_unlock(&philo->arg->protect_output);
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
			|| philo->arg->must_eat == -1))
	{
		right = (philo->id + 1) % philo->arg->number;
		eating(philo, right);
		philo->state = SLEEP;
		print_it(philo, SLEEP, 0);
		pthread_mutex_unlock(&philo->arg->forks[philo->id]);
		pthread_mutex_unlock(&philo->arg->forks[right]);
		start_sleep = get_time();
		usleep(philo->arg->time_tosleep * 1000 - 14000);
		while (get_time() - start_sleep < philo->arg->time_tosleep)
			;
		print_it(philo, THINKING, 0);
	}
	return (NULL);
}
