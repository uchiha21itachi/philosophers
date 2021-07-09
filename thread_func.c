#include "philosophers.h"

void    print_with_mutex(char *str,t_parse *parse, int phil_num)
{
    pthread_mutex_lock(&parse->tab->print);
    printf("%lu %d %s\n",get_time() - parse->tab->philo[parse->id].last_meal, phil_num, str);
    pthread_mutex_unlock(&parse->tab->print);
}

void    pick_fork(t_parse *parse, int sec_phil)
{
    pthread_mutex_lock(&parse->tab->philo[parse->id].fork);
    pthread_mutex_lock(&parse->tab->philo[sec_phil].fork);
    print_with_mutex("has taken fork", parse, parse->id);
    print_with_mutex("has taken fork", parse, parse->id);
}

void    drop_fork(t_parse *parse, int sec_phil)
{
    pthread_mutex_unlock(&parse->tab->philo[parse->id].fork);
    pthread_mutex_unlock(&parse->tab->philo[sec_phil].fork);
    // print_with_mutex("has dropped the fork", parse, parse->id);
    // print_with_mutex("has dropped the fork", parse, parse->id);
    parse->tab->philo[parse->id].total_meals++;
}

    // printf("id [%d] total_meals [%d] required [%d]\n",
    // parse->id, parse->tab->philo[parse->id].total_meals,
    // parse->tab->total_time_eat);
int     check_meal(t_parse *parse)
{
    if (parse->tab->total_time_eat <= 0)
        return 0;
    if (parse->tab->philo[parse->id].total_meals >= parse->tab->total_time_eat)
        return (1);
    else
        return (0);
}

void    *function(void *data)
{
    t_parse         *parse;
    int             sec_phil;
    int             i;

    parse = (t_parse *)data;
    sec_phil = parse->id + 1;
    if (sec_phil == parse->tab->total_philo)
        sec_phil = 0;
    i = check_meal(parse);
    if (i == 1)
        return (NULL);
    pick_fork(parse, sec_phil);
    pthread_mutex_lock(&parse->tab->death);
    parse->tab->philo[parse->id].last_meal = get_time();
    print_with_mutex("Is eating", parse, parse->id);
    pthread_mutex_unlock(&parse->tab->death);
    usleep(1000 * parse->tab->time_eat);
    drop_fork(parse, sec_phil);
    print_with_mutex("Is sleeping", parse, parse->id);
    usleep(1000 * parse->tab->time_sleep);
    print_with_mutex("Is thinking", parse, parse->id);
    // i = check
    if (i == 0)
        function(data);
    return (0);
}