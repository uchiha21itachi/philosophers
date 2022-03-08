/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassharm <yassharm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 21:39:08 by yassharm          #+#    #+#             */
/*   Updated: 2022/03/08 21:41:47 by yassharm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_with_mutex(char *str, t_philo *p)
{
	pthread_mutex_lock(&p->data->print);
	if (check_state_status(p, 0) == 0)
		printf("%lu\t %d\t %s\n", (get_time() - p->data->start_time), p->id, str);
	pthread_mutex_unlock(&p->data->print);
}

void	pick_fork(t_philo *p)
{
	pthread_mutex_lock(&p->l_fork);
	print_with_mutex("has taken left fork", p);
	if (p->r_fork == NULL)
	{
		usleep(1000 * (p->data->time_die * 2));
		pthread_mutex_unlock(&p->l_fork);
		return ;
	}
	pthread_mutex_lock(p->r_fork);
	print_with_mutex("has taken right fork", p);
	set_pstate(p, 0);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death);
	philo->last_meal = get_time();
	print_with_mutex("Is eating", philo);
	pthread_mutex_unlock(&philo->data->death);
	usleep(1000 * philo->data->time_eat);
	drop_fork(philo);
	set_pstate(philo, 1);
	pthread_mutex_lock(&philo->count_meal);
	philo->total_meals++;
	pthread_mutex_unlock(&philo->count_meal);
}

void	drop_fork(t_philo *p)
{
	pthread_mutex_unlock(&p->l_fork);
	pthread_mutex_unlock(p->r_fork);
}

void	sleeping(t_philo *philo)
{
	print_with_mutex("Is sleeping", philo);
	usleep(1000 * philo->data->time_sleep);
	set_pstate(philo, -1);
	print_with_mutex("Is thinking", philo);
}
