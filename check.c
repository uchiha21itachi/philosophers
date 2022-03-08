/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassharm <yassharm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 00:10:21 by yassharm          #+#    #+#             */
/*   Updated: 2022/03/09 00:11:02 by yassharm         ###   ########.fr       */
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
	if (data->time_die <= 0 || data->time_die > int_max
		|| data->time_eat <= 0 || data->time_eat > int_max)
	{
		printf("Error in time_to_die or time_to_eat\n");
		return (-1);
	}
	if (data->time_sleep <= 0 || data->time_sleep > int_max)
	{
		printf("Error in time_to_sleep\n");
		return (-1);
	}
	if (data->total_time_eat == 0)
		return (-1);
	return (0);
}
