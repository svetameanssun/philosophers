/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervising.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svetameanssun <svetameanssun@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 18:00:40 by stitovsk          #+#    #+#             */
/*   Updated: 2024/08/26 15:18:29 by svetameanss      ###   ########.fr       */
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
			if (philo[i].mls_eaten == philo->data->mls_to_eat)
			{
				full_philos++;
			}
			i++;
		}
	}
	if (full_philos == philo->data->philos_nbr)
	{
		philo->data->philos_full = full_philos;
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
	}
	return (philo);
}
