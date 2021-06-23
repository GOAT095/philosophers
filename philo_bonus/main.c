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

void	print_it(int i, t_philo *philo)
{
	sem_wait(philo->arg->protect_output);
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
	else if (i == THINKING)
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
		ft_putnbr_fd(philo->id + 1, 1);
		ft_putstr_fd(" is dead\n", 1);
		return ;
	}
	sem_post(philo->arg->protect_output);
}

void	eating(t_philo *philo, int right)
{
	sem_wait(philo->arg->forks);
	print_it(LEFT_FORK, philo);
	sem_wait(philo->arg->forks);
	print_it(RIGHT_FORK, philo);
	philo->state = EAT;
	print_it(EAT, philo);
	philo->last_eat = get_time();
	philo->eat_counter++;
	sleep_it(philo->arg->time_toeat, philo->arg);
	sem_post(philo->arg->forks);
	sem_post(philo->arg->forks);
}

void	check_eat_death(t_philo *philo, t_arg *arg)
{
	int	i;

	while (1)
	{
		
		if (philo->state != EAT
			&& ((get_time() - philo->last_eat) >= arg->time_todie))
		{
			print_it(DEAD, philo);
			exit(3);
		}
		if (philo->eat_counter == arg->must_eat)
		{
			pthread_join(philo->t, NULL);
			exit(4);
		}
		usleep(90);
	}
}

int	main(int ac, char **av)
{
	t_philo	*philo;
	t_arg	arg;
	int		i;
	int		x;

	if (ac < 5 || ac > 6)
		return (fail("error arguments number\n"));
	if (!(check_args(av)))
		return (fail("error arguments\n"));
	arg.number = 0;
	get_args(&arg, av, ac, &philo);
	init_philo(philo, &arg);
	i = 0;
	sem_unlink("print");
	arg.protect_output = sem_open("print", O_CREAT, 0644, 1);
	arg.program_start = get_time();
	while (i < arg.number)
	{
		philo[i].pid = fork();
		if (philo[i].pid == 0)
		{
			pthread_create(&philo[i].t, NULL, philo_funcn, &philo[i]);
			check_eat_death(&philo[i], &arg);
		}
		i++;
	}
	while (waitpid(-1, &x, 0) >= 0)
	{
		if (WIFEXITED(x) && (WEXITSTATUS(x) == 3))
			kill_all(philo, &arg);
	}
	return (0);
}
