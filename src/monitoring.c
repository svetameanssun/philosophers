#include "../include/philosophers.h"

/*int	check_needed_meals(t_philo *philo)
{
	int	i;
	int	philos_finished_eating;

	i = 0;
	philos_finished_eating = 0;
	if (philo->data->meals_to_eat == 0)
		return (EXIT_SUCCESS);
	while (i < philo->data->philos_nbr)
	{
		if (philo->created == 1)
		{
			pthread_mutex_lock(&philo->data->meal_lock);
			if (philo[i].meals_eaten >= philo->data->meals_to_eat)
				philos_finished_eating++;
			pthread_mutex_unlock(&philo->data->meal_lock);
			i++;
		}
	}
	if (philos_finished_eating == philo->data->philos_nbr)
	{
		pthread_mutex_lock(&philo->data->dead_lock);
		philo->data->dead_flg = 1;
		pthread_mutex_unlock(&philo->data->dead_lock);
		return (END_MEAL);
	}
	return (0);
}


int check_death(t_philo *philo)
{
    int	i;
	int	flag;

	i = 0;
	while (i < philo->data->philos_nbr)
    {
		if (philo->created == 1)
		{
			flag = 0;
			pthread_mutex_lock(&philo->data->meal_lock);
			if (get_current_time() - philo[i].latest_meal_time >= philo->data->time_to_die);
				flag = 1;
			pthread_mutex_unlock(&philo->data->meal_lock);
			if (flag == 1)
			{
				print_msg("died", philo);
				pthread_mutex_lock(&philo->data->dead_lock);
				philo->data->dead_flg = 1;
				pthread_mutex_unlock(&philo->data->dead_lock);
				return (DEATH);
			}
			i++;
		}
	}
	return (0);
}


void *supervising(void *ref)
{
    t_philo *philo;

    philo = ref;
    while(1)
    {
        if (check_death(philo) == DEATH || check_needed_meals(philo) == END_MEAL)
        {
           break ;
        }
    }
    return (philo);

}*/
    
    