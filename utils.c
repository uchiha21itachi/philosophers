#include "philosophers.h"

void	print_parse_data(t_data *data)
{
	int	i;

	i = 0;
	printf("Total_philo [%d]\n", data->total_philo);
    printf("Time to die [%d]\n", data->time_die);
    printf("Time to eat [%d]\n", data->time_eat);
    printf("Time to sleep[%d]\n", data->time_sleep);
    printf("Total number of required meals[%d]\n",
    data->total_time_eat);
    while (i < data->total_philo)
    {
        printf("philosopher number [%d]\n", data->philo[i].id);
        printf("philo total_meals [%d]\n", data->philo[i].total_meals);
        printf("philo Last Meal [%lu]\n", data->philo[i].last_meal);
        i++;
    }
}

void	print_parsed_philo(t_parse *parse)
{
	// int i;

	// i = 0;
	// while (i < data->total_philo)
	// {
		printf("parse-> id [%d] \n", parse->id);
		printf("philo last meal [%lu]\n total meals [%d]\n",
		parse->tab->philo[parse->id].last_meal,
		parse->tab->philo[parse->id].total_meals);
		// i++;
	// }
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

unsigned long get_time(void)
{
    struct timeval  tp;
    unsigned long   temp;

    gettimeofday(&tp, NULL);
    temp = (tp.tv_sec * 1000) + (tp.tv_usec / 1000);
    return (temp);
}

void	free_all(t_data *data, t_parse **parse)
{
	int i;

	i = -1;
	while (++i < data->total_philo)
		free(parse[i]);
	free(parse);
	free(data->philo);
	free(data);
}