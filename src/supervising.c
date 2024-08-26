/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervising.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stitovsk <stitovsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 20:55:33 by stitovsk          #+#    #+#             */
/*   Updated: 2024/08/26 20:55:34 by stitovsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	check_needed_meals(t_philo *philo)
{
	int	i;
	int	full_philos;

	i = 0;
	full_philos = 0;
	while (i < philo->data->philos_nbr)
	{
		if (philo[i].created == 1)
		{
			pthread_mutex_lock(&philo->data->meal_lock);
			if (philo[i].mls_eaten == philo->data->mls_to_eat)
			{
				full_philos++;
			}
			pthread_mutex_unlock(&philo->data->meal_lock);
			i++;
		}
	}
	if (full_philos == philo->data->philos_nbr)
	{
		return (END_MEAL);
	}
	return (0);
}

int	check_death(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->philos_nbr)
	{
		if (philo[i].created == 1)
		{
			if ((get_current_time() - philo[i].last_meal)
				> (size_t)philo->data->time_to_die)
			{
				usleep(100);
				safe_print("died", philo);
				set_dead_flag(philo->data, 1);
				return (DEATH);
			}
			i++;
		}
	}
	return (0);
}

void	*supervising(void *ref)
{
	t_philo	*philo;

	philo = ref;
	ms_sleep(100);
	while (1)
	{
		if (check_death(philo) == DEATH
			|| check_needed_meals(philo) == END_MEAL)
		{
			return (NULL);
		}
		ms_sleep(10);
	}
	return (philo);
}
