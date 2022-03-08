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
    int             nb_clean_exit;
    int             state;
    pthread_mutex_t print;
    pthread_mutex_t death;
    pthread_mutex_t state_m;
    pthread_mutex_t finish;
    pthread_mutex_t clean_exit;
}               t_data;

typedef struct s_philo
{
    int             id;
    int             total_meals;
    int             pstate;
    unsigned long   last_meal;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    t_data          *data;
    
    pthread_t       thread_id;
    pthread_t       thread_death_id;

    pthread_mutex_t pstate_m;
    pthread_mutex_t eating;
    pthread_mutex_t count_meal;
    pthread_mutex_t l_fork;
    pthread_mutex_t *r_fork;    
}               t_philo;

typedef struct s_parse
{
    t_data  *data;
    t_philo *philo;
}           t_parse;



/* parsing.c */
int             check_data(t_data *data);
int             init_data_mutex(t_data *data);
t_data          *data_init(int argc, char **argv);
int             init_philo_mutex(t_parse *parse, int i);
int             philo_init(t_parse  *parse);

/* utils.c */
int             is_all_num(char *str);
int	            ft_atoi(const char *str);

/* main.c */
int             check_args(int ac, char **av);
unsigned long   get_time(void);
void	        free_all (t_parse *parse);


int check_all_out(t_data *data);
void    *wait_death(void *p);

void            print_with_mutex(char *str, t_philo *p);
void            pick_fork(t_philo *p);
void            drop_fork(t_philo *p);
void            *check_death(void *p);
int             check_meal(t_philo *p);
void            eating(t_philo *philo);
void           *function(void *parse);
void            set_pstate(t_philo *philo, int i);
int             check_state_status(t_philo *p, int i);
void            do_things(t_philo *philo);
void	        print_parse_data(t_parse *parse);
void            sleeping(t_philo *p);
void	        print_parsed_philo(t_parse *parse);


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
// void    do_things(t_philo *philo)
// {
//     while(check_state_status(philo, 0) == 0)
//     {
//         if (philo->p_state == -1)
//             pick_fork(philo);
//         else if (philo->p_state == 0)
//         {
//             eating(philo);
//             if (check_meal(philo))
//                 break;
//         }
//         else if (philo->p_state == 1)
//             sleeping(philo);
//     }
//     if (philo->p_state == 0)
//         drop_fork(p);
//     pthread_mutex_lock(&philo->data->clean_exit);
//     philo->data->nb_clean_exit++;
//     pthread_mutex_unlock(&philo->data->clean_exit);
//     return;
// }

t_data     *data_init(int argc, char **argv)
{
    t_data  *data;

    data = (t_data *)malloc(sizeof(t_data));
    if (data == NULL)
    {
        printf("Malloc error in cond_init\n");
        return (NULL);
    }
    data->start_time = 0;
    data->total_philo = ft_atoi(argv[1]);
    data->time_die = ft_atoi(argv[2]);
    data->time_eat = ft_atoi(argv[3]);
    data->time_sleep = ft_atoi(argv[4]);
    data->state = 0;
    data->nb_clean_exit = 0;
    if (data->total_philo <= 0 || data->total_philo > 2147483647)
    {
        printf("Error in number of philosophers\n");
        return (NULL);
    }
    else if (data->time_die == 0 || data->time_die > 2147483647)
    {
        printf("Error in time_to_die\n");
        return (NULL);
    }
    else if(data->time_eat == 0 || data->time_eat > 2147483647)
    {
        printf("Error in time_to_eat\n");
        return (NULL);
    }
    else if(data->time_sleep == 0 || data->time_sleep > 2147483647)
    {
        printf("Error in time_to_sleep\n");
        return (NULL);
    }

    if (argc == 6)
        data->total_time_eat = ft_atoi(argv[5]);
    else
        data->total_time_eat = -1;
    pthread_mutex_init(&data->print, NULL);
    pthread_mutex_init(&data->death, NULL);
    pthread_mutex_init(&data->state_m, NULL);
    pthread_mutex_init(&data->clean_exit, NULL);
    pthread_mutex_init(&data->finish, NULL);
    return (data);
}
void    philo_init(t_parse  *parse)
{
    int             i;

    i = 0;
    while (i < parse->data->total_philo)
    {
        parse->philo[i].id = i+1;
        parse->philo[i].total_meals = 0;
        parse->philo[i].last_meal = 0;
        parse->philo[i].pstate = -1;
        pthread_mutex_init(&parse->philo[i].pstate_m, NULL);
        pthread_mutex_init(&parse->philo[i].l_fork, NULL);
        pthread_mutex_init(&parse->philo[i].eating, NULL);
        pthread_mutex_init(&parse->philo[i].count_meal, NULL);
        if (parse->data->total_philo == 1)
        {
            parse->philo[i].r_fork = NULL;
            return;
        }
        if (i == (parse->data->total_philo - 1))
            parse->philo[i].r_fork = &parse->philo[0].l_fork;
        else
            parse->philo[i].r_fork = &parse->philo[i + 1].l_fork;
        i++;
    }
}
    
*/