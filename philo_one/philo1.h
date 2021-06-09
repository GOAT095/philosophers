#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include "../libft/libft.h"

typedef struct s_arg
{
    int number;
    unsigned long time_todie;
    unsigned long time_toeat;
    unsigned long time_tosleep;
    int must_eat;
    pthread_mutex_t *forks;
} t_arg;

typedef struct s_philo
{
    unsigned long last_eat;
    int eat_counter;
    pthread_t t;
    t_arg *arg;
    int state;
} t_philo;