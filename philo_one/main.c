/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anassif <anassif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 16:05:34 by anassif           #+#    #+#             */
/*   Updated: 2021/06/09 16:19:38 by anassif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo1.h>

int ft_strlen(char *str)
{
    int i = 0;
    if (!str)
        return (i);
    while (str[i])
        i++;
    return (i);
}

int fail(char *str)
{
    write(1, str, ft_strlen(str));
    return(1);
}

void get_args(t_philo *philo, char **av)
{
    philo->arg->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * (int)av[0]);
}

int main (int ac, char **av)
{
    t_philo philo;
    if (ac != 5)
        return (fail("Error: argument\n"));
    get_args(&philo, av);
    
}