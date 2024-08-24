/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervising.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svetameanssun <svetameanssun@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:27:01 by svetameanss       #+#    #+#             */
/*   Updated: 2024/08/24 16:29:01 by svetameanss      ###   ########.fr       */
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
			if (philo[i].meals_eaten == philo->data->meals_to_eat)
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
			if ((get_current_time() - philo[i].latest_meal_time)
				> (size_t)philo->data->time_to_die)
			{
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
