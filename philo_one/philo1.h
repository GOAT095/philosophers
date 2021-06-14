#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include "../libft/libft.h"

#define start 0
#define eat 1
#define sleep 2
#define thinking 3
#define dead 4
#define left_fork 5
#define right_fork 6

typedef struct s_arg
{
    int number;
    unsigned long long time_todie;
    unsigned long long time_toeat;
    unsigned long long time_tosleep;
    int must_eat;
    pthread_mutex_t *forks;
    pthread_mutex_t protect_output;
} t_arg;

typedef struct s_philo
{
    int id;
    unsigned long long last_eat;
    int eat_counter;
    pthread_t t;
    t_arg *arg;
    int state;
} t_philo;