/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anassif <anassif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 20:08:21 by anassif           #+#    #+#             */
/*   Updated: 2021/06/15 21:06:44 by anassif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

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
	unsigned long long	time_todie;
	unsigned long long	time_toeat;
	unsigned long long	time_tosleep;
	int					must_eat;
	pthread_mutex_t		*forks;
	pthread_mutex_t		protect_output;
}				t_arg;

typedef struct s_philo
{
	int					id;
	unsigned long long	last_eat;
	int					eat_counter;
	pthread_t			t;
	t_arg				*arg;
	int					state;
}				t_philo;

int	ft_strlen(const char *str);
int	ft_atoi(const char *str);
int	fail(char *str);
#endif