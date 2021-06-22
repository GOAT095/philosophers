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
		printf("%llu %d is eating\n",
			get_time() - philo->arg->program_start, philo->id + 1);
	else if (i == LEFT_FORK || i == RIGHT_FORK)
		printf("%llu %d has taken a fork\n",
			get_time() - philo->arg->program_start, philo->id + 1);
	else if (i == THINKING)
		printf("%llu %d is thinking\n",
			get_time() - philo->arg->program_start, philo->id + 1);
	else if (i == SLEEP)
		printf("%llu %d is sleeping\n",
			get_time() - philo->arg->program_start, philo->id + 1);
	else if (i == DEAD)
		printf("%llu %d is dead\n",
			get_time() - philo->arg->program_start, philo->id + 1);
	sem_post(philo->arg->protect_output);
}

void	eating(t_philo *philo, int right)
{
	sem_wait(philo->arg->forks);
	print_it(LEFT_FORK, philo);
	sem_wait(philo->arg->forks);
	print_it(RIGHT_FORK, philo);
	print_it(EAT, philo);
	philo->last_eat = get_time();
	philo->eat_counter++;
	philo->state = EAT;
	sleep_it(philo->arg->time_toeat, philo->arg);
}

void	check_eat_death(t_philo philo, t_arg *arg)
{
	int	i;

	while (1)
	{
		if (philo.state != EAT
			&& ((get_time() - philo.last_eat) >= arg->time_todie))
		{
			print_it(DEAD, &philo);
			exit(3);
		}
		if (philo.eat_counter == arg->must_eat)
		{
			pthread_join(philo.t, NULL);
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
	i = -1;
	sem_unlink("print");
	arg.protect_output = sem_open("print", O_CREAT, 0644, 1);
	arg.program_start = get_time();
	while (++i < arg.number)
	{
		printf("time now is {%llu}\n",
			get_time() - philo->arg->program_start);
		philo[i].pid = fork();
		if (philo[i].pid == 0)
		{
			pthread_create(&philo[i].t, NULL, philo_funcn, &philo[i]);
			check_eat_death(philo[i], &arg);
		}
	}
	while (waitpid(-1, &x, 0) >= 0)
	{
		if (WIFEXITED(x) && (WEXITSTATUS(x) == 3))
			kill_all(philo, &arg);
	}
	return (0);
}
