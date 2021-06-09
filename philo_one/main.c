/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anassif <anassif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 16:05:34 by anassif           #+#    #+#             */
/*   Updated: 2021/06/09 17:12:25 by anassif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo1.h"



int fail(char *str)
{
    write(1, str, ft_strlen(str));
    return(1);
}

void get_args(t_philo *philo, char **av, int ac)
{
    philo->arg = malloc(sizeof(t_arg));
    philo->arg->forks = malloc(sizeof(pthread_mutex_t) * (int)ft_atoi(av[1]));
    philo->arg->number = ft_atoi(av[1]);
    philo->arg->must_eat = -1;
    philo->arg->time_todie = ft_atoi(av[2]);
    philo->arg->time_toeat = ft_atoi(av[3]);
    philo->arg->time_tosleep = ft_atoi(av[4]);
    if (ac == 6)
        philo->arg->must_eat = ft_atoi(av[5]);
}

int main (int ac, char **av)
{
    t_philo philo;
    if (ac < 5 || ac > 6)
        return (fail("error arguments number"));
    get_args(&philo, av, ac);
    printf("%d %lu %lu %lu %d", philo.arg->number, philo.arg->time_todie, 
        philo.arg->time_toeat, philo.arg->time_tosleep, philo.arg->must_eat);
    return (0);
}