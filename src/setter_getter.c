/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter_getter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stitovsk <stitovsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:42:16 by stitovsk          #+#    #+#             */
/*   Updated: 2024/08/27 17:50:21 by stitovsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	is_created(t_philo *philo)
{
	int	created_flg;

	pthread_mutex_lock(&philo->data->aux_lock);
	created_flg = philo->created;
	pthread_mutex_unlock(&philo->data->aux_lock);
	return (created_flg);
}

void	set_created_flag(t_philo *philo, t_supper *data)
{
	pthread_mutex_lock(&data->aux_lock);
	philo->created = 1;
	pthread_mutex_unlock(&data->aux_lock);
}

int	is_full(t_philo *philo)
{
	int	full;

	pthread_mutex_lock(&philo->data->meal_lock);
	full = philo->mls_eaten == philo->data->mls_to_eat;
	pthread_mutex_unlock(&philo->data->meal_lock);
	return (full);
}

void	add_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->mls_eaten++;
	pthread_mutex_unlock(&philo->data->meal_lock);
}

void	set_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(&philo->data->meal_lock);
}

int	check_time(t_philo *philo)
{
	int	time;

	pthread_mutex_lock(&philo->data->meal_lock);
	time = (get_current_time() - philo->last_meal)
		> (size_t)philo->data->time_to_die;
	pthread_mutex_unlock(&philo->data->meal_lock);
	return (time);
}
