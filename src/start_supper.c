/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_supper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svetameanssun <svetameanssun@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:26:54 by svetameanss       #+#    #+#             */
/*   Updated: 2024/08/24 16:26:55 by svetameanss      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	init_forks(pthread_mutex_t mutexes[], t_supper *data)
{
	int	i;

	i = 0;
	while (i < data->philos_nbr)
	{
		pthread_mutex_init(&mutexes[i], NULL);
		i++;
	}
	data->forks_list = mutexes;
}

void	destroy_forks(pthread_mutex_t mutexes[], t_supper *data)
{
	int	i;

	i = 0;
	while (i < data->philos_nbr)
	{
		pthread_mutex_destroy(&mutexes[i]);
		i++;
	}
}

void	assign_forks(t_supper*data, t_philo *philo)
{
	philo->my_fork = &data->forks_list[philo->id];
	if (data->philos_nbr == 1)
	{
		return ;
	}
	else if (data->philos_nbr > 1)
	{
		if (philo->id == 0)
			philo->other_fork = &data->forks_list[philo->fork_nbr - 1];
		else
			philo->other_fork = &data->forks_list[philo->id - 1];
	}
}

void	init_philosopher(t_philo *philo, t_supper *data, int id)
{
	philo->im_full = 0;
	philo->meals_eaten = 0;
	philo->id = id;
	philo->data = data;
	philo->fork_nbr = data->philos_nbr;
	pthread_create(&(philo->my_thread), NULL, &routine, philo);
	philo->latest_meal_time = get_current_time();
	philo->start_time = get_current_time();
	assign_forks(data, philo);
	philo->created = 1;
}

void	gather_philosophers(t_philo *philo_arr, t_supper *data)
{
	pthread_t	thread;
	int	i;

	i = 0;
	pthread_create(&thread, NULL, &supervising, philo_arr);
	while (i < data->philos_nbr)
	{
		init_philosopher(&philo_arr[i], data, i);
		i++;
	}
	i = 0;
	while (i < data->philos_nbr)
	{
		pthread_join(philo_arr[i].my_thread, NULL);
		i++;
	}
	pthread_join(thread, NULL);
}
