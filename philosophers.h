/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassharm <yassharm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 22:07:16 by yassharm          #+#    #+#             */
/*   Updated: 2022/03/08 22:13:36 by yassharm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	unsigned long	start_time;
	int				total_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				total_time_eat;
	int				nb_clean_exit;
	int				death_clean_exit;
	int				state;
	int				error;
	pthread_mutex_t	print;
	pthread_mutex_t	death;
	pthread_mutex_t	state_m;
	pthread_mutex_t	finish;
	pthread_mutex_t	clean_exit;
}		t_data;

typedef struct s_philo
{
	int				id;
	int				total_meals;
	int				pstate;
	unsigned long	last_meal;
	t_data			*data;
	pthread_t		thread_id;
	pthread_t		thread_death_id;
	pthread_mutex_t	pstate_m;
	pthread_mutex_t	eating;
	pthread_mutex_t	count_meal;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*r_fork;
}		t_philo;

typedef struct s_parse
{
	t_data	*data;
	t_philo	*philo;
}		t_parse;

/* parsing.c */
int				check_data(t_data *data);
int				init_data_mutex(t_data *data);
t_data			*data_init(int argc, char **argv);
int				init_philo_mutex(t_parse *parse, int i);
int				philo_init(t_parse *parse);

/* utils.c */
int				is_all_num(char *str);
int				ft_atoi(const char *str);
void			free_data_mutex(t_parse *parse);
void			free_all(t_parse *parse);

/* main.c */
int				check_args(int ac, char **av);
unsigned long	get_time(void);

/* Thread_func.c */
void			*function(void *parse);
void			*wait_philo(void *p);
void			*check_death(void *p);
void			*wait_death(void *p);

/*Activities.c */
void			sleeping(t_philo *p);
void			drop_fork(t_philo *p);
void			eating(t_philo *philo);
void			pick_fork(t_philo *p);
void			print_with_mutex(char *str, t_philo *p);

/*philosopher.c.c */
int				check_all_out(t_data *data);
int				check_state_status(t_philo *p, int i);
void			set_pstate(t_philo *philo, int i);
int				check_meal(t_philo *p);
int				check_all_death_out(t_data *data);

#endif
