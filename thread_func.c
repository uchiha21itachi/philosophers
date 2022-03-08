/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassharm <yassharm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 21:56:15 by yassharm          #+#    #+#             */
/*   Updated: 2022/03/08 22:17:39 by yassharm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	increase_death_clean_exit(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->clean_exit);
	philo->data->death_clean_exit++;
	pthread_mutex_unlock(&philo->data->clean_exit);
}

void	*check_death(void *p)
{
	t_philo			*philo;
	unsigned long	temp;

	philo = (t_philo *)p;
	while (check_state_status(philo, 0) == 0 && !check_meal(p))
	{
		usleep(100 * (philo->data->time_die));
		pthread_mutex_lock(&philo->data->death);
		if (philo->last_meal == 0)
			temp = philo->data->start_time;
		else
			temp = philo->last_meal;
		if ((get_time() - temp) >= (unsigned long)philo->data->time_die)
		{
			print_with_mutex("Is dead", philo);
			check_state_status(philo, 1);
			pthread_mutex_unlock(&philo->data->death);
			increase_death_clean_exit(philo);
			return (0);
		}
		pthread_mutex_unlock(&philo->data->death);
	}
	increase_death_clean_exit(philo);
	return (0);
}

void	*function(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	pthread_create(&philo->thread_death_id, NULL, check_death, (void *)philo);
	while (!(check_meal(philo)) && (check_state_status(philo, 0) == 0))
	{
		if (philo->pstate == -1)
			pick_fork(philo);
		else if (philo->pstate == 0)
		{
			eating(philo);
			if (check_meal(philo))
				break ;
		}
		else if (philo->pstate == 1)
			sleeping(philo);
	}
	if (philo->pstate == 0)
		drop_fork(p);
	pthread_mutex_lock(&philo->data->clean_exit);
	philo->data->nb_clean_exit++;
	pthread_mutex_unlock(&philo->data->clean_exit);
	return (0);
}

void	*wait_philo(void *p)
{
	t_parse	*parse;
	int		i;
	void	*ret;

	parse = (t_parse *)p;
	while (!check_all_out(parse->data))
	{
		usleep(100);
	}
	i = -1;
	while (++i < parse->data->total_philo)
		pthread_join(parse->philo[i].thread_id, &ret);
	usleep(100);
	return (0);
}

void	*wait_death(void *p)
{
	t_parse	*parse;
	int		i;
	void	*ret;

	parse = (t_parse *)p;
	while (!check_all_death_out(parse->data))
	{
		usleep(100);
	}
	i = -1;
	while (++i < parse->data->total_philo)
		pthread_join(parse->philo[i].thread_death_id, &ret);
	usleep(100);
	return (0);
}
