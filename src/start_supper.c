/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_supper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stitovsk <stitovsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 20:54:26 by stitovsk          #+#    #+#             */
/*   Updated: 2024/08/27 17:35:48 by stitovsk         ###   ########.fr       */
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
			philo->other_fork = &data->forks_list[philo->data->philos_nbr - 1];
		else
			philo->other_fork = &data->forks_list[philo->id - 1];
	}
}

void	init_philosopher(t_philo *philo, t_supper *data, int id)
{
	philo->id = id;
	philo->mls_eaten = 0;
	philo->data = data;
	philo->last_meal = get_current_time();
	philo->start_time = get_current_time();
	assign_forks(data, philo);
}

void	gather_philosophers(t_philo *philo_arr, t_supper *data)
{
	pthread_t	thread;
	int			i;

	i = 0;
	while (i < data->philos_nbr)
	{
		init_philosopher(&philo_arr[i], data, i);
		i++;
	}
	pthread_create(&thread, NULL, &supervising, philo_arr);
	i = 0;
	while (i < data->philos_nbr)
	{
		pthread_create(&philo_arr[i].my_thread, NULL, &routine, &philo_arr[i]);
		set_created_flag(&philo_arr[i], data);
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
