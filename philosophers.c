#include "philosophers.h"

void    philo_init(t_data *data)
{
    int             i;
    unsigned long    cur_time;

    i = 0;
    data->philo = (t_philo *)malloc(sizeof(t_philo) * data->total_philo);
    if (data->philo == NULL)
    {
        printf("Error in Malloc in philo_init\n");
        return ;
    }
    cur_time = get_time();
    printf("cur time in start %lu\n", cur_time);
    pthread_mutex_init(&data->print, NULL);
    pthread_mutex_init(&data->death, NULL);
    while (i < data->total_philo)
    {
        data->philo[i].id = i;
        data->philo[i].total_meals = 0;
        data->philo[i].last_meal = cur_time;
        pthread_mutex_init(&data->philo[i].fork, NULL);
        i++;
    }
}

t_data  *cond_init(int argc, char **argv)
{
    t_data  *data;

    if (!(argc == 5 || argc == 6))
    {
        printf("wrong nummber of arguments\n");
        return(NULL);
    }
    data = (t_data *)malloc(sizeof(t_data));
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
    philo_init(data);
    return (data);
}

t_parse **func_data_init(t_data *data)
{
    t_parse **parse;
    int     i;

    parse = (t_parse **)malloc(sizeof(t_parse *) * data->total_philo);
    if (parse == 0)
    {
        printf("malloc error 01funcdatainit\n");
        return (NULL);
    }
    i = 0;
    while (i < data->total_philo)
    {
        parse[i] = (t_parse *)malloc(sizeof(t_parse));
        if (parse[i] == NULL)
        {
            printf("malloc error funcdatainit\n");
            return (NULL);
        }
        parse[i]->id = i;
        parse[i]->tab = data;
        i++;
    }
    return (parse);
}

int main(int argc, char **argv)
{
    t_data  *data;
    t_parse **parse_data;
    void    *ret;
    int     i;

    i = 0;
    data = cond_init(argc, argv);
    parse_data = func_data_init(data);
    // print_parse_data(data);
    // print_parsed_philo(parse_data[i]);
    while (i < data->total_philo)
    {
        pthread_create(&data->philo[i].thread_id, NULL, function, (void *)parse_data[i]);
        // usleep(10000);
        // pthread_detach(data->philo[i].thread_id);
        i++;
    }
    i = -1;
    while (++i < data->total_philo)
        pthread_join(data->philo[i].thread_id, &ret);
    i = -1;
    while (++i < data->total_philo)
        pthread_mutex_destroy(&data->philo[i].fork);
    pthread_mutex_destroy(&data->print);
    pthread_mutex_destroy(&data->death);
    free_all(data, parse_data);
   return (0);
}