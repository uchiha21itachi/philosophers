#include "philosophers.h"

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

unsigned long get_time(void)
{
    struct timeval  tp;
    unsigned long   temp;

    gettimeofday(&tp, NULL);
    temp = (tp.tv_sec * 1000) + (tp.tv_usec / 1000);
    return (temp);
}

void    create_philo_threads(t_parse *parse, int r)
{
    int     i;

    i = 0;
    while (i < parse->data->total_philo)
    {
        if (i % 2 == r)
        {
            parse->philo[i].data = parse->data;
            pthread_create(&parse->philo[i].thread_id, NULL, function, (void *)&parse->philo[i]);
            usleep(50);
        }
        i++;
    }
    usleep(100); 
}

void    create_threads(t_parse *parse)

{
    pthread_t       gather_philo;
    pthread_t       gather_death;
    // int              i;
    // void            *ret;

    parse->data->start_time = get_time();
    create_philo_threads(parse, 0);    
    create_philo_threads(parse, 1);
    pthread_create(&gather_philo, NULL, wait_philo, (void *)parse);
    pthread_create(&gather_death, NULL, wait_death, (void *)parse);
    pthread_join(gather_philo, NULL);
    pthread_join(gather_death, NULL);
    // i = -1;
    // while (++i < parse->data->total_philo)
        // pthread_join(parse->philo[i].thread_id, &ret);
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
    if (philo_init(&parse) == -1)
    {
        printf("Error in initializing philosophers\n");
        return (-1);
    }
    create_threads(&parse);
    free_all(&parse);
    return (0);
}