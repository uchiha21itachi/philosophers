#include "philosophers.h"

void    *check_death(void *p)
{
    t_philo         *philo;
    unsigned long   temp;

    philo = (t_philo *)p;

    while(check_state_status(philo,0) == 0 && !check_meal(p))
    {
        // usleep(1000 * (philo->data->time_die));
        usleep(1000 * (100));
        pthread_mutex_lock(&philo->data->death);
        if (philo->last_meal == 0)
            temp = philo->data->start_time;
        else
            temp = philo->last_meal;
        if ((get_time() - temp) >= (unsigned long)philo->data->time_die)
        {
            print_with_mutex("Is dead", philo);
            check_state_status(philo, 1);
            pthread_mutex_unlock(&philo->data->death);
            return (0);
        }
        pthread_mutex_unlock(&philo->data->death);
    }
    return (0);
}

void    *function(void *p)
{
    t_philo     *philo;

    philo = (t_philo *)p;
    pthread_create(&philo->thread_death_id, NULL, check_death, (void *)philo);
    while(!(check_meal(philo)) && (check_state_status(philo, 0) == 0))
    {   
        if (philo->pstate == -1)
            pick_fork(philo);
        else if (philo->pstate == 0)
        {
            eating(philo);
            if (check_meal(philo))
                break;
        }
        else if (philo->pstate == 1)
            sleeping(philo);
    }
    if (philo->pstate == 0)
        drop_fork(p);
    pthread_detach(philo->thread_death_id);
    pthread_mutex_lock(&philo->data->clean_exit);
    philo->data->nb_clean_exit++;
    pthread_mutex_unlock(&philo->data->clean_exit);
    return(0);
}

void    *wait_death(void *p)
{
    t_parse  *parse;
    int     i;
    void     *ret;

    parse = (t_parse *)p;
    while(!check_all_out(parse->data))
    {
        usleep(100);
    }
    i = -1;
    pthread_mutex_lock(&parse->data->print);
    printf("total number of all_out %d", parse->data->nb_clean_exit);
    pthread_mutex_unlock(&parse->data->print);
    while (++i < parse->data->total_philo)
        pthread_join(parse->philo[i].thread_id, &ret);
    usleep(100);
    return (0);
}

















/*
if(philo->pstate == 0)
        // {
        //     print_with_mutex("pstate 0 has both forks someone died\n", philo);
        //     drop_fork(philo);
        // }
        // else if (philo->pstate == 1)
        // {
        //     print_with_mutex("pstate 1 Weird state ready to eat but has forks\n", philo);
        // }
        // else if (philo->pstate == 2)
        //     print_with_mutex("pstate 2 \n", philo);
        // else if (philo->pstate == 3)
        //     print_with_mutex("pstate 3 thinking \n", philo);
        // else
        //     print_with_mutex("pstate -1 default \n", philo);
    pstate = -1 // start
    pstate = 0 // picked both fork
    pstate = 1 // ready to eat
    pstate = 2 // dropped forks
    pstate = 3 // slept & thinking now
*/