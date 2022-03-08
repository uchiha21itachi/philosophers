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

int	ft_isspace_isdigit(char c, char d)
{
	if (d == 's')
	{
		if (c == ' ' || c == '\t' || c == '\n'
			|| c == '\v' || c == '\f' || c == '\r')
			return (1);
	}
	else if (d == 'd')
	{
		if (c >= 48 && c <= 57)
			return (1);
	}
	else if (d == 'b')
	{
		if (c == ' ' || c == '\t' || c == '\n'
			|| c == '\v' || c == '\f' || c == '\r'
			|| (c >= 48 && c <= 57))
			return (1);
	}
	return (0);
}


int	ft_atoi(const char *str)
{
	int		sign;
	int		result;

	sign = 1;
	result = 0;
	while (ft_isspace_isdigit(*str, 's'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*(str++) == '-')
			sign *= -1;
	}
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
		{
			result *= 10;
			result += (*(str++) - '0');
		}
		else
			return (result * sign);
	}
	return (result * sign);
}


void	free_all (t_parse *parse)
{
	int		i;

	i = -1;
	while (++i < parse->data->total_philo)
	{
        if (pthread_mutex_destroy(&parse->philo[i].l_fork) != 0)
			printf("error in mutex l_fork");
        if (pthread_mutex_destroy(&parse->philo[i].pstate_m) != 0)
			printf("error in mutex pstate_m");
        if (pthread_mutex_destroy(&parse->philo[i].eating) != 0)
			printf("error in mutex eating");
        if (pthread_mutex_destroy(&parse->philo[i].count_meal) != 0)
			printf("error in mutex count_meals");
	}
    if (pthread_mutex_destroy(&parse->data->print) != 0)
		printf("error in mutex print");
	if (pthread_mutex_destroy(&parse->data->death) != 0)
		printf("error in mutex death");
    if (pthread_mutex_destroy(&parse->data->finish) != 0)
		printf("error in mutex finish");
    if (pthread_mutex_destroy(&parse->data->clean_exit) != 0)
		printf("error in mutex clean_exit");
    if (pthread_mutex_destroy(&parse->data->state_m) != 0)
		printf("error in mutex state_m");
	free(parse->data);
	free(parse->philo);
}