/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stitovsk <stitovsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 20:56:21 by stitovsk          #+#    #+#             */
/*   Updated: 2024/08/27 17:48:05 by stitovsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define BUFF 200
# define ERROR_ARG_NUM 1
# define ERROR_ARG 6
# define ERROR_NUMBER 2
# define ERROR_MALLOC 3
# define DEATH 4
# define END_MEAL 5

# define ERROR_ATOI -1
/*
number_of_philosophers

time_to_die -           If a philosopher didn’t start eating time_to_die
(in milliseconds)       milliseconds since the beginning of their last meal
                        or the beginning of the simulation, they die.

time_to_eat -           The time it takes for a philosopher to eat.
(in milliseconds)       During that time, they will need to hold two forks.

time_to_sleep - The time a philosopher will spend sleeping.
(in milliseconds)

[number_of_times_each_philosopher_must_eat] - If all philosophers have eaten
(optional argument)       at least number_of_times_each_philosopher_must_eat
                                              times, the simulation stops.

*/
typedef struct the_last_supper
{
	int				philos_nbr;
	int				dead_flg;
	int				mls_to_eat;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	aux_lock;
	pthread_mutex_t	*forks_list;
}			t_supper;

typedef struct philosopher
{
	int				id;
	int				created;
	int				mls_eaten;
	//int				fork_nbr;
	size_t			start_time;
	size_t			last_meal;
	t_supper		*data;
	pthread_t		my_thread;
	pthread_mutex_t	*my_fork;
	pthread_mutex_t	*other_fork;
}		t_philo;

void	*supervising(void *ref);
int		check_args(char **argv, t_supper *data);
int		is_number(char *str);
int		ft_atoi(char *str);
int		ft_isspace(int c);
void	gather_philosophers(t_philo *philo_arr, t_supper *data);
void	init_forks(pthread_mutex_t mutexes[], t_supper *data);
void	destroy_forks(pthread_mutex_t mutexes[], t_supper *data);
void	init_philosopher(t_philo *philo, t_supper *data, int id);
void	assign_forks(t_supper*data, t_philo *philo);
void	*routine(void *ref);
size_t	get_current_time(void);
int		smbd_dead(t_supper *data);
int		print_msg(char *msg, t_philo *philo);
int		action_sequence(t_philo *philo);
int		check_death(t_philo *philo);
int		check_needed_meals(t_philo *philo);
void	ms_sleep(size_t msec);
int		uwait(int time, t_philo *philo);
void	set_dead_flag(t_supper *data, int dead_flag);
void	safe_print(char *msg, t_philo *philo);
int		is_created(t_philo *philo);
void	set_created_flag(t_philo *philo, t_supper *data);
void	add_meal(t_philo *philo);
int		is_full(t_philo *philo);
void	set_time(t_philo *philo);
int		check_time(t_philo *philo);

#endif