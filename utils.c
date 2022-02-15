#include "philosophers.h"

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

unsigned long get_time(void)
{
    struct timeval  tp;
    unsigned long   temp;

    gettimeofday(&tp, NULL);
    temp = (tp.tv_sec * 1000) + (tp.tv_usec / 1000);
    return (temp);
}

void	free_all (t_parse *parse)
{
	int	i;

	i = -1;
	while (++i < parse->data->total_philo)
	{
        pthread_mutex_destroy(&parse->philo[i].l_fork);
        pthread_mutex_destroy(&parse->philo[i].pstate_m);
	}
    pthread_mutex_destroy(&parse->data->print);
    pthread_mutex_destroy(&parse->data->death);
    pthread_mutex_destroy(&parse->data->finish);
    pthread_mutex_destroy(&parse->data->pick);
    pthread_mutex_destroy(&parse->data->state_m);
	free(parse->data);
	free(parse->philo);
}