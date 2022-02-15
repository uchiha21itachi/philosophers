#include "philosophers.h"

int     is_all_num(char *str)
{
    int     i;

    i  = 0;
    while(str[i])
    {
        if (str[i] < 48 || str[i] > 57)
            return (1);
        i++;
    }
    return (0);
}

int     check_args(int ac, char **av)
{
    int     i;

    if (!(ac == 5 || ac == 6))
    {
        printf("wrong nummber of arguments\n");
        return(1);
    }
    i = 1;
    while (i < ac)
    {
        if (is_all_num(av[i]))
            return (1);
        i++;
    }
    return (0);
}

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
    pthread_mutex_init(&data->pick, NULL);
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

void    create_threads(t_parse *parse)
{
    int     i;
    void    *ret;

    i = 0;
    parse->data->start_time = get_time();
    while (i < parse->data->total_philo)
    {
        if (i % 2 == 0)
        {
            parse->philo[i].data = parse->data;
            pthread_create(&parse->philo[i].thread_id, NULL, function, (void *)&parse->philo[i]);
            usleep(50);
        }
        i++;
    }
    i = 0;
    while (i < parse->data->total_philo)
    {
        if (i % 2 != 0)
        {
            parse->philo[i].data = parse->data;
             pthread_create(&parse->philo[i].thread_id, NULL, function, (void *)&parse->philo[i]);
            usleep(50);
        }
        i++;
    }
    i = -1;
    while (++i < parse->data->total_philo)
        pthread_join(parse->philo[i].thread_id, &ret);
}

int     main(int ac, char **av)
{
    t_parse     parse;

    if (check_args(ac, av))
    {
        printf("Error in Arguments\n");
        return (-1);
    }
    parse.data = data_init(ac, av);
    if (parse.data == NULL)
        return (-1);
    parse.philo = (t_philo *)malloc(sizeof(t_philo) * parse.data->total_philo);
    if (parse.philo == NULL)
    {
        printf("Malloc Error \n");
        return (-1);
    }
    philo_init(&parse);
    create_threads(&parse);
    free_all(&parse);
    return (0);
}