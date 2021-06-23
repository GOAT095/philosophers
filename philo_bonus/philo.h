/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anassif <anassif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 20:08:21 by anassif           #+#    #+#             */
/*   Updated: 2021/06/17 17:03:31 by anassif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>

# define START 0
# define EAT 1
# define SLEEP 2
# define THINKING 3
# define DEAD 4
# define LEFT_FORK 5
# define RIGHT_FORK 6

typedef struct s_arg
{
	int					all_eat;
	int					number;
	unsigned long long	program_start;
	unsigned long long	time_todie;
	unsigned long long	time_toeat;
	unsigned long long	time_tosleep;
	int					must_eat;
	sem_t				*forks;
	sem_t				*protect_output;
}				t_arg;

typedef struct s_philo
{
	int					id;
	pid_t				pid;
	unsigned long long	last_eat;
	int					eat_counter;
	pthread_t			t;
	t_arg				*arg;
	int					state;
}				t_philo;

int					ft_strlen(const char *str);
int					ft_atoi(const char *str);
int					check_args(char **av);
int					fail(char *str);
void				get_args(t_arg *arg, char **av, int ac, t_philo **philo);
unsigned long long	get_time(void);
void				init_philo(t_philo *philo, t_arg *arg);
void				*philo_funcn(void *data);
void				check_eat_death(t_philo *philo, t_arg *arg);
void				eating(t_philo *philo, int right);
void				kill_all(t_philo *philo, t_arg *arg);
void				sleep_it(unsigned long long time, t_arg *arg);
void				print_it(int i, t_philo *philo);
void				ft_putnbr_fd(int n, int fd);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
#endif