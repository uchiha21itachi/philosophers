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

typedef struct s_data
{
    int             total_philo;
    int             time_die;
    int             time_eat;
    int             time_sleep;
    int             total_time_eat;
    pthread_mutex_t print;
    pthread_mutex_t death;
    t_philo *philo;
}               t_data;

typedef struct s_parse
{
    int     id;
    t_data  *tab;
}           t_parse;

int	            ft_atoi(const char *str);
void	        print_parse_data(t_data *data);
unsigned long   get_time(void);
void	        print_parsed_philo(t_parse *parse);
void           *function(void *data);
void	        free_all(t_data *data, t_parse **parse);

#endif