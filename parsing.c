/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassharm <yassharm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 21:48:15 by yassharm          #+#    #+#             */
/*   Updated: 2022/03/08 21:52:51 by yassharm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_data(t_data *data)
{
	int	int_max;

	int_max = 2147483647;
	if (data->total_philo <= 0 || data->total_philo > int_max)
	{
		printf("Error in number of philosophers\n");
		return (-1);
	}
	else if (data->time_die <= 0 || data->time_die > int_max)
	{
		printf("Error in time_to_die\n");
		return (-1);
	}
	else if (data->time_eat <= 0 || data->time_eat > int_max)
	{
		printf("Error in time_to_eat\n");
		return (-1);
	}
	else if (data->time_sleep <= 0 || data->time_sleep > int_max)
	{
		printf("Error in time_to_sleep\n");
		return (-1);
	}
	printf("time to die %d\n", data->time_die);
	return (0);
}

int	init_data_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->print, NULL) != 0)
	{
		printf("Error in initalizing mutex print\n");
		return (-1);
	}
	if (pthread_mutex_init(&data->death, NULL) != 0)
	{
		printf("Error in initalizing mutex death\n");
		return (-1);
	}
	if (pthread_mutex_init(&data->state_m, NULL) != 0)
	{
		printf("Error in initalizing mutex state_m\n");
		return (-1);
	}
	if (pthread_mutex_init(&data->clean_exit, NULL) != 0)
	{
		printf("Error in initalizing mutex clean_exit\n");
		return (-1);
	}
	if (pthread_mutex_init(&data->mdeath_clean_exit, NULL) != 0)
	{
		printf("Error in initalizing mutex clean_exit\n");
		return (-1);
	}
	if (pthread_mutex_init(&data->finish, NULL) != 0)
	{
		printf("Error in initalizing mutex finish\n");
		return (-1);
	}
	return (0);
}

t_data	*data_init(int argc, char **argv)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (data == NULL)
	{
		printf("Malloc error in cond_init\n");
		return (NULL);
	}
	data->start_time = 0;
	data->nb_clean_exit = 0;
	data->death_clean_exit = 0;
	data->state = 0;
	data->total_philo = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->total_time_eat = ft_atoi(argv[5]);
	else
		data->total_time_eat = -1;
	if (check_data(data) != 0 || init_data_mutex(data) != 0)
		return (NULL);
	return (data);
}

int	init_philo_mutex(t_parse *parse, int i)
{
	if (pthread_mutex_init(&parse->philo[i].pstate_m, NULL) != 0)
	{
		printf("Error in initalizing mutex pstate for philo[%d]\n", i);
		return (-1);
	}
	if (pthread_mutex_init(&parse->philo[i].l_fork, NULL) != 0)
	{
		printf("Error in initalizing mutex l_fork for philo[%d]\n", i);
		return (-1);
	}
	if (pthread_mutex_init(&parse->philo[i].eating, NULL) != 0)
	{
		printf("Error in initalizing mutex eating for philo[%d]\n", i);
		return (-1);
	}
	if (pthread_mutex_init(&parse->philo[i].count_meal, NULL) != 0)
	{
		printf("Error in initalizing mutex count_meal for philo[%d]\n", i);
		return (-1);
	}
	return (0);
}

int	philo_init(t_parse *parse)
{
	int	i;

	i = 0;
	while (i < parse->data->total_philo)
	{
		parse->philo[i].id = i + 1;
		parse->philo[i].total_meals = 0;
		parse->philo[i].last_meal = 0;
		parse->philo[i].pstate = -1;
		if (init_philo_mutex(parse, i) != 0)
			return (-1);
		if (parse->data->total_philo == 1)
		{
			parse->philo[i].r_fork = NULL;
			return (0);
		}
		if (i == (parse->data->total_philo - 1))
			parse->philo[i].r_fork = &parse->philo[0].l_fork;
		else
			parse->philo[i].r_fork = &parse->philo[i + 1].l_fork;
		i++;
	}
	return (0);
}
