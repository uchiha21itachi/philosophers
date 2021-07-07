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
    temp = tp.tv_sec;
    // printf("temp [%lu]\n", temp);
    temp = tp.tv_usec;
    // printf("temp [%lu]\n", temp);
    temp = (tp.tv_sec * 1000) + (tp.tv_usec / 1000);
    printf("temp [%lu]\n", temp);
    return (temp);
}

void    philo_init(t_cond *data)
{
    int             i;
    unsigned int    cur_time;
    unsigned int    now_time;

    i = 0;
    data->philo = (t_philo *)malloc(sizeof(t_philo) * data->total_philo);
    if (data->philo == NULL)
    {
        printf("Error in Malloc in philo_init\n");
        return ;
    }
    cur_time = get_time();
    usleep(2000000
    );
    now_time = get_time();
    printf("time diff [%u]\n", (now_time - cur_time));
    while (i < data->total_philo)
    {
        data->philo[i].id = i;
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
    
    // printf("Total_philo [%d]\n", data->total_philo);
    // printf("Time to die [%d]\n", data->time_die);
    // printf("Time to eat [%d]\n", data->time_eat);
    // printf("Time to sleep[%d]\n", data->time_sleep);
    // printf("Total number of required meals[%d]\n",
    // data->total_time_eat);
    // while (i < data->total_philo)
    // {
    //     printf("philosopher number [%d]\n", data->philo[i].id);
    //     i++;
    // }
    free(data->philo);
    free(data);
   return (0);
}