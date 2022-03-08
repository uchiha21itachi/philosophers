#include "philosophers.h"

//total meal 0 check this please
int     check_meal(t_philo *p)
{
    pthread_mutex_lock(&p->data->finish);
    if (p->data->total_time_eat <= 0)
    {
        pthread_mutex_unlock(&p->data->finish);
        return 0;
    }
    if (p->total_meals >= p->data->total_time_eat)
    {
        pthread_mutex_unlock(&p->data->finish);
        return (1);
    }
    pthread_mutex_unlock(&p->data->finish);
    return (0);
}

void    set_pstate(t_philo *philo, int i)
{
    pthread_mutex_lock(&philo->pstate_m);
    philo->pstate = i;
    pthread_mutex_unlock(&philo->pstate_m);
}

int    check_state_status(t_philo *philo, int i)
{
    pthread_mutex_lock(&philo->data->state_m);
    if (i == 1)
        philo->data->state = 1;
    if (philo->data->state)
    {
        pthread_mutex_unlock(&philo->data->state_m);
        return(1);
    }
    pthread_mutex_unlock(&philo->data->state_m);
    return(0);
}

int check_all_out(t_data *data)
{
    pthread_mutex_lock(&data->clean_exit);
    if (data->nb_clean_exit >= data->total_philo)
    {
        pthread_mutex_unlock(&data->clean_exit);
        return (1);
    }
    pthread_mutex_unlock(&data->clean_exit);
    return (0);
}