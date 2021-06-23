/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anassif <anassif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 21:49:21 by anassif           #+#    #+#             */
/*   Updated: 2021/06/17 17:33:25 by anassif          ###   ########.fr       */
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

void	sleep_it(unsigned long long time, t_arg *arg)
{
	unsigned long long	start_sleep;

	start_sleep = get_time();
	usleep(time * 1000 - 20000);
	while (get_time() - start_sleep < time)
		;
}

void	*philo_funcn(void *data)
{
	t_philo				*philo;
	int					right;

	philo = data;
	while (philo->eat_counter < philo->arg->must_eat
		|| philo->arg->must_eat == -1)
	{
		eating(philo, right);
		print_it(SLEEP, philo);
		philo->state = SLEEP;
		sleep_it(philo->arg->time_tosleep, philo->arg);
		print_it(THINKING, philo);
		philo->state = THINKING;
	}
	return (NULL);
}

void	kill_all(t_philo *philo, t_arg *arg)
{
	int	i;

	i = 0;
	while (i < arg->number)
	{
		kill(philo[i].pid, SIGKILL);
		i++;
	}
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	int	nbr;

	nbr = n;
	if (nbr == -2147483648)
	{
		ft_putchar_fd('-', fd);
		ft_putchar_fd('2', fd);
		ft_putnbr_fd(147483648, fd);
		return ;
	}
	if (nbr < 0)
	{
		ft_putchar_fd('-', fd);
		nbr = -nbr;
	}
	if (nbr > 9)
	{
		ft_putnbr_fd(nbr / 10, fd);
		ft_putchar_fd(nbr % 10 + '0', fd);
	}
	else if (nbr <= 9)
	{
		ft_putchar_fd(nbr + '0', fd);
	}
}

void	ft_putstr_fd(char *s, int fd)
{
	int i;

	i = 0;
	if (!s)
		return ;
	while (s[i] != '\0')
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}
