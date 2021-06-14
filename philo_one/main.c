/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anassif <anassif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 16:05:34 by anassif           #+#    #+#             */
/*   Updated: 2021/06/14 16:22:59 by anassif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo1.h"

int fail(char *str)
{
    write(1, str, ft_strlen(str));
    return(1);
}

int check_args(char **av)
{
    int j;
    int i;

    i = 1;
    while(av[i])
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

void get_args(t_arg *arg, char **av, int ac,t_philo **philo)
{
    int i;

    i = 0;
    arg->forks = malloc(sizeof(pthread_mutex_t) * (int)ft_atoi(av[1]));
    arg->number = ft_atoi(av[1]);
    arg->must_eat = -1;
    arg->time_todie = ft_atoi(av[2]);
    arg->time_toeat = ft_atoi(av[3]);
    arg->time_tosleep = ft_atoi(av[4]);
    if (ac == 6)
        arg->must_eat = ft_atoi(av[5]);
    while (i < arg->number)
    {
        pthread_mutex_init(&arg->forks[i], NULL);
        i++;
    }
    *philo = (t_philo *)malloc(sizeof(t_philo) * arg->number);
}

unsigned long long get_time()
{
    struct timeval time;

    gettimeofday(&time, NULL);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void    init_philo(t_philo *philo, t_arg *arg)
{
    int i;

    i = 0;
    while (i < arg->number)
    {
        philo[i].id = i;
        philo[i].last_eat = get_time();
        philo[i].eat_counter = 0;
        philo[i].arg = arg;
        philo[i].state = start;
        i++;
    }
}

void        *philo_funcn(void *data)
{
    t_philo     *philo;

    philo = data;
    while (philo->eat_counter < philo->arg->must_eat || philo->arg->must_eat == -1)
    {
        unsigned long long start_sleep;
    
        printf("\033[0;32m%d is thinking\n", philo->id + 1);
        pthread_mutex_lock(&philo->arg->forks[philo->id]);
        printf("\033[0;31mphilo %d has taken left fork\n", philo->id + 1);
        pthread_mutex_lock(&philo->arg->forks[(philo->id + 1) % philo->arg->number]);
        printf("\033[0;31mphilo %d has taken right fork\n", philo->id + 1);
        printf("\033[0;32mphilo %d is eating\n", philo->id + 1);
        philo->eat_counter++;
        philo->last_eat = get_time();
        usleep(philo->arg->time_toeat * 1000 - 14000);
        while (get_time() - philo->last_eat < philo->arg->time_toeat)
            ;
        philo->state = eat;
        pthread_mutex_unlock(&philo->arg->forks[(philo->id + 1) % philo->arg->number]);
        pthread_mutex_unlock(&philo->arg->forks[philo->id]);
        philo->state = sleep;
        printf("\033[0;32mphilo %d is sleeping\n", philo->id + 1);
        start_sleep = get_time();
        usleep(philo->arg->time_tosleep * 1000 - 1400);
        while (get_time() - start_sleep < philo->arg->time_tosleep)
            ;
    }
    return (NULL);
}

int main (int ac, char **av)
{
    t_philo *philo;
    t_arg   arg;
    int     i;

    if (ac < 5 || ac > 6)
        return (fail("error arguments number\n"));
    if (!(check_args(av)))
        return (fail("error arguments\n"));
    arg.number = 0;
    get_args(&arg, av, ac, &philo);
    // printf("%d %lu %lu %lu %d", philo.arg->number, philo.arg->time_todie, 
    //     philo.arg->time_toeat, philo.arg->time_tosleep, philo.arg->must_eat);
    printf("%d\n", arg.number);
    init_philo(philo, &arg);
    i = 0;
    while (i < arg.number)
    {
        pthread_create(&philo[i].t, NULL, philo_funcn, &philo[i]);
        usleep(100);
        i++;
    }
    while (1)
    {
        usleep(100);
    }
    return (0);
}