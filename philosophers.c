#include "philosophers.h"


void    *check_death(void *p)
{
    t_philo     *philo;

    (void)philo;

    philo = (t_philo *)p;
    usleep(1000 * (philo->data->time_die));
    if (check_state_status(philo,0) == 1)
        return (0);
    pthread_mutex_lock(&philo->data->death);
    if (check_meal(p))
        return (0);
    if (philo->last_meal == 0)
    { 
        if ((get_time() - philo->data->start_time) >= (unsigned long)philo->data->time_die)
        {
            print_with_mutex("Is dead", philo);
            check_state_status(philo, 1);
            pthread_mutex_unlock(&philo->data->death);
            return (0);
        }
        pthread_mutex_unlock(&philo->data->death);
        return (0);
    }
    if ((get_time() - philo->last_meal) >= (unsigned long)philo->data->time_die)
    {
        print_with_mutex("Is dead", philo);
        check_state_status(philo, 1);
        pthread_mutex_unlock(&philo->data->death);
        return (0);
    }
    pthread_mutex_unlock(&philo->data->death);
    return (0);
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

int     check_meal(t_philo *p)
{
    if (p->data->total_time_eat <= 0)
        return 0;
    pthread_mutex_lock(&p->data->finish);
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

void    do_things(t_philo *philo)
{
    if (check_state_status(philo, 0) == 0)
        pick_fork(philo);
    if (check_state_status(philo, 0) == 0)
    {
        eating(philo);
        if (check_state_status(philo, 0) == 0)
            usleep(1000 * philo->data->time_eat);
        drop_fork(philo);
        set_pstate(philo, 2);
        if (check_meal(philo))
            return;
        print_with_mutex("Is sleeping", philo);
        if (check_state_status(philo, 0) == 0)
            usleep(1000 * philo->data->time_sleep);
        set_pstate(philo, 3);
        print_with_mutex("Is thinking", philo);
    }
    return;
}












