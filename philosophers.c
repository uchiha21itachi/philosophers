#include "philosophers.h"

t_cond  *cond_init(int argc, char **argv)
{
    t_cond  *data;

    if (!(argc == 5 || argc == 6))
    {
        printf("wrong nummber of arguments\n");
        return(NULL);
    }
    data = (t_cond *)malloc(sizeof(t_cond));
    if (data == NULL)
    {
        printf("Malloc error in cond_init\n");
        return (NULL);
    }
    data->total_philo = ft_atoi(argv[1]);
    data->time_die = ft_atoi(argv[2]);
    data->time_eat = ft_atoi(argv[3]);
    data->time_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        data->total_time_eat = ft_atoi(argv[5]);
    else
        data->total_time_eat = -1;
    return (data);
}

unsigned long get_time(void)
{
    struct timeval  tp;
    unsigned long   temp;

    gettimeofday(&tp, NULL);
    temp = (tp.tv_sec * 1000) + (tp.tv_usec / 1000);
    return (temp);
}

void    philo_init(t_cond *data)
{
    int             i;
    unsigned int    cur_time;

    i = 0;
    data->philo = (t_philo *)malloc(sizeof(t_philo) * data->total_philo);
    if (data->philo == NULL)
    {
        printf("Error in Malloc in philo_init\n");
        return ;
    }
    cur_time = get_time();
    while (i < data->total_philo)
    {
        data->philo[i].id = i;
        data->philo[i].total_meals = 0;
        data->philo[i].last_meal = cur_time;
        pthread_mutex_init(&data->philo[i].fork, NULL);
        i++;
    }
}

int main(int argc, char **argv)
{
    t_cond  *data;
    int      i;

    i = 0;
    data = cond_init(argc, argv);
    philo_init(data);
    print_parse_data(data);
    while (i < data->total_philo)
    {
        pthread_mutex_destroy(&data->philo[i].fork);
        i++;
    }
    free(data->philo);
    free(data);
   return (0);
}