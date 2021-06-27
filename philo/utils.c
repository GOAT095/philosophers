/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anassif <anassif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 19:56:36 by anassif           #+#    #+#             */
/*   Updated: 2021/06/27 15:59:58 by anassif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

unsigned long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	get_args(t_arg *arg, char **av, int ac, t_philo **philo)
{
	int	i;

	i = -1;
	arg->forks = malloc(sizeof(pthread_mutex_t) * (int)ft_atoi(av[1]));
	arg->number = ft_atoi(av[1]);
	if (arg->number == 0)
		return ;
	arg->must_eat = -1;
	arg->all_eat = 0;
	arg->time_todie = ft_atoi(av[2]);
	arg->time_toeat = ft_atoi(av[3]);
	arg->time_tosleep = ft_atoi(av[4]);
	arg->program_start = get_time();
	if (ac == 6)
		arg->must_eat = ft_atoi(av[5]);
	while (++i < arg->number)
		pthread_mutex_init(&arg->forks[i], NULL);
	pthread_mutex_init(&arg->protect_output, NULL);
	*philo = (t_philo *)malloc(sizeof(t_philo) * arg->number);
}
