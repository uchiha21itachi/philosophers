#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_philo
{
    int             id;
    int             total_meals;
    unsigned long   last_meal;
    pthread_t       thread_id;
    pthread_mutex_t fork;
}               t_philo;

typedef struct s_cond
{
    int     total_philo;
    int     time_die;
    int     time_eat;
    int     time_sleep;
    int     total_time_eat;
    t_philo *philo;

}               t_cond;

int	    ft_atoi(const char *str);

#endif