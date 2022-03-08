/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassharm <yassharm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 21:41:55 by yassharm          #+#    #+#             */
/*   Updated: 2022/03/09 00:13:35 by yassharm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_args(int ac, char **av)
{
	int	i;

	if (!(ac == 5 || ac == 6))
	{
		printf("wrong nummber of arguments\n");
		return (1);
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

unsigned long	get_time(void)
{
	struct timeval	tp;
	unsigned long	temp;

	gettimeofday(&tp, NULL);
	temp = (tp.tv_sec * 1000) + (tp.tv_usec / 1000);
	return (temp);
}

void	create_philo_threads(t_parse *p, int r)
{
	int	i;

	i = 0;
	while (i < p->data->total_philo)
	{
		if (i % 2 == r)
		{
			p->philo[i].data = p->data;
			pthread_create(&p->philo[i].thread_id, NULL,
				function, (void *)&p->philo[i]);
			usleep(50);
		}
		i++;
	}
	usleep(100);
}

void	create_threads(t_parse *parse)

{
	pthread_t	gather_philo;
	pthread_t	gather_death;

	parse->data->start_time = get_time();
	create_philo_threads(parse, 0);
	create_philo_threads(parse, 1);
	pthread_create(&gather_philo, NULL, wait_philo, (void *)parse);
	pthread_create(&gather_death, NULL, wait_death, (void *)parse);
	pthread_join(gather_philo, NULL);
	pthread_join(gather_death, NULL);
}

int	main(int ac, char **av)
{
	t_parse	parse;

	if (check_args(ac, av))
	{
		printf("Error in Arguments\n");
		return (-1);
	}
	parse.data = data_init(ac, av);
	if (parse.data->error == 1 || init_data_mutex(parse.data) != 0)
	{
		free(parse.data);
		return (-1);
	}
	if (philo_init(&parse) == -1)
	{
		printf("Error in initializing philosophers\n");
		if (parse.philo)
			free(parse.philo);
		return (-1);
	}
	create_threads(&parse);
	free_all(&parse);
	free_data_mutex(&parse);
	return (0);
}
