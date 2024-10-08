/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stitovsk <stitovsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 20:55:18 by stitovsk          #+#    #+#             */
/*   Updated: 2024/08/27 18:28:07 by stitovsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	smbd_dead(t_supper *data)
{
	int	dead_flag;

	pthread_mutex_lock(&data->dead_lock);
	dead_flag = data->dead_flg;
	pthread_mutex_unlock(&data->dead_lock);
	return (dead_flag);
}

void	set_dead_flag(t_supper *data, int dead_flag)
{
	pthread_mutex_lock(&data->dead_lock);
	data->dead_flg = dead_flag;
	pthread_mutex_unlock(&data->dead_lock);
}

int	action_sequence(t_philo *philo)
{
	print_msg("has taken a fork", philo);
	pthread_mutex_lock(philo->my_fork);
	if (philo->data->philos_nbr == 1)
	{
		pthread_mutex_unlock(philo->my_fork);
		uwait(philo->data->time_to_die, philo);
		set_dead_flag(philo->data, 1);
		printf("%zu %d died\n",
			get_current_time() - philo->start_time, philo->id + 1);
		return (uwait(philo->data->time_to_die, philo));
	}
	pthread_mutex_lock(philo->other_fork);
	print_msg("has taken a fork", philo);
	print_msg("is eating", philo);
	set_time(philo);
	add_meal(philo);
	pthread_mutex_unlock(philo->my_fork);
	pthread_mutex_unlock(philo->other_fork);
	uwait(philo->data->time_to_eat, philo);
	if (philo->mls_eaten == philo->data->mls_to_eat || smbd_dead(philo->data))
		return (1);
	print_msg("is sleeping", philo);
	uwait(philo->data->time_to_sleep, philo);
	print_msg("is thinking", philo);
	return (0);
}

void	*routine(void *ref)
{
	t_philo	*philo;

	philo = ref;
	if (philo->id % 2 != 0)
		uwait(1, philo);
	while (1)
	{
		if (action_sequence(philo) != 0)
			return (NULL);
	}
	return (philo);
}
