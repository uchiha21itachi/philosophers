#include "philosophers.h"

void    print_with_mutex(char *str, t_philo *p)
{
    pthread_mutex_lock(&p->data->print);
    if (check_state_status(p, 0) == 0)
        printf("%lu\t %d\t %s\n",(get_time() - p->data->start_time), p->id, str);
    pthread_mutex_unlock(&p->data->print);
}

void    pick_fork(t_philo *p)
{
    pthread_mutex_lock(&p->l_fork);
    print_with_mutex("has taken left fork", p);
    if (p->r_fork == NULL)
    {   
        usleep(1000 * (p->data->time_die * 2));
        pthread_mutex_unlock(&p->l_fork);
        return;
    }
    if (check_state_status(p, 0))
    {
        pthread_mutex_unlock(&p->l_fork);
        return;
    }
    pthread_mutex_lock(p->r_fork);
    print_with_mutex("has taken right fork", p);
    set_pstate(p, 0);
}

void    drop_fork(t_philo *p)
{
    pthread_mutex_unlock(&p->l_fork);
    // print_with_mutex("has dropped left fork", p);
    pthread_mutex_unlock(p->r_fork);
    // print_with_mutex("has dropped right fork", p);
    pthread_mutex_lock(&p->data->finish);
    p->total_meals++;
    pthread_mutex_unlock(&p->data->finish);
}

void    eating(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->finish);
    philo->last_meal = get_time();
    print_with_mutex("Is eating", philo);
    pthread_mutex_unlock(&philo->data->finish);
}
    
void    *function(void *p)
{
    t_philo     *philo;

    philo = (t_philo *)p;
    while(!(check_meal(philo)) && (check_state_status(philo, 0) == 0))
    {
        pthread_create(&philo->thread_death_id, NULL, check_death, (void *)philo);
        do_things(philo); 
        pthread_detach(philo->thread_death_id);

        pthread_mutex_lock(&philo->pstate_m);
        if(philo->pstate == 0)
        {
            print_with_mutex("pstate 0 has both forks someone died\n", philo);
            drop_fork(philo);
        }
        // else if (philo->pstate == 1)
        // {
        //     print_with_mutex("pstate 1 Weird state ready to eat but has forks\n", philo);
        // }
        // else if (philo->pstate == 2)
        //     print_with_mutex("pstate 2 Weird state ready to eat but has forks\n", philo);
        // else if (philo->pstate == 3)
        //     print_with_mutex("pstate 3 thinking \n", philo);
        // else
        //     print_with_mutex("pstate -1 default \n", philo);
        philo->pstate = -1;
        pthread_mutex_unlock(&philo->pstate_m);
    }
    return(0);  
}

/*
    pstate = -1 // start
    pstate = 0 // picked both fork
    pstate = 1 // ready to eat
    pstate = 2 // dropped forks
    pstate = 3 // slept & thinking now
*/