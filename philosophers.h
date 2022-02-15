#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_data
{
    unsigned long   start_time;
    int             total_philo;
    int             time_die;
    int             time_eat;
    int             time_sleep;
    int             total_time_eat;
    int             state;
    pthread_mutex_t print;
    pthread_mutex_t death;
    pthread_mutex_t state_m;
    pthread_mutex_t finish;
    pthread_mutex_t pick;

}               t_data;

typedef struct s_philo
{
    int             id;
    int             total_meals;
    unsigned long   last_meal;
    int             pstate;
    t_data          *data;
    pthread_t       thread_id;
    pthread_t       thread_death_id;
    pthread_mutex_t pstate_m;
    pthread_mutex_t l_fork;
    pthread_mutex_t *r_fork;
}               t_philo;

typedef struct s_parse
{
    t_data  *data;
    t_philo *philo;
}           t_parse;

void            print_with_mutex(char *str, t_philo *p);
void            pick_fork(t_philo *p);
void            drop_fork(t_philo *p);
void            *check_death(void *p);
int     check_meal(t_philo *p);
void    eating(t_philo *philo);

void           *function(void *parse);
void    set_pstate(t_philo *philo, int i);

int             check_state_status(t_philo *p, int i);
void            do_things(t_philo *philo);
int	            ft_atoi(const char *str);
void	        print_parse_data(t_parse *parse);
unsigned long   get_time(void);
void	        print_parsed_philo(t_parse *parse);
void	        free_all (t_parse *parse);



#endif


















/*

    philo 1 takes both fork
    philo 2 waits
        - It can die while waiting to pick fork
        - Need to check the death when it reaches pick_fork
        - Need to check death after time_to_die ms
        - If it does not die then it eats then drop fork
            -It can die while thinking sleeping 
    philo 3 takes both fork
    philo 4 waits


    - Best solution is to create a death thread for each philo that keep checking if philo is dead or not
    - If philo dies it locks all the mutex
    - Need to tell other threads that they should stop the process and exit
    - If other thread try to access the mutex then it will fuck up


  Solution sudo steps

    - Create a thread that calls a do_activity() 
    - Thread must keep on checking the death for particular thread
    - It checks every time_to_die ms

        -   Create_death_thread(NULL, do_activity)
                -   void    do_activity(NULL) // It will check death
        -   Pick forks()
        -   eat()
        -   drop_fork()
        -   sleeping()
        -   thinking()
        -   check_status of how many meals and data->state;
            if (1)
                go to pick fork again (need pick fork inside while)
            else
                clean_exit


    -- problem - 
        Need to understand what a clean exit is?

        -Once any on n death_thread find the philo is dead
        -Need to stop other philo whatever they are doing
            -trying to pick up fork
            -trying to eat
            -trying to drop forks
            -trying to print sleeping
            -trying to print thinking
    

    doubts
        - Time of last meal should be when philo start eating or when it finish eating
            -icamyplant did the time since it starts eating
        time_to_die (in milliseconds): 
        If a philosopher didn’t start eating time_to_die
        milliseconds since the beginning of their last meal
        or the beginning of the simulation, they die.






//garbage
    // pthread_mutex_lock(&philo->data->print);
    // printf("I returned this %d\n", i);
    // printf("start_time [%lu] Current time [%lu] last_meal [%lu] diff [%lu]\n",philo->data->start_time, get_time(), philo->last_meal, (get_time() - philo->last_meal));
    // printf("philo [%d] last_meals [%lu] \n", philo->id, philo->last_meal);
    // pthread_mutex_unlock(&philo->data->print);

//in case of one philosopher there is going to be no r_fork
//It should start the thread wait till it die and exit
//
//It is wise to create a death thread for each philo which keeps checking the death of particular phio.
//Creating a death thread is confusing at the moment. 
//Need testing
//
//Need to check the custom usleep function. Apparantly it is useful
//

*/