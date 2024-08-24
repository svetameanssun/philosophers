/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svetameanssun <svetameanssun@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:26:28 by svetameanss       #+#    #+#             */
/*   Updated: 2024/08/24 16:26:29 by svetameanss      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	manage_errors(int error)
{
	if (error == ERROR_ARG_NUM)
		printf("Wrong ammount of arguments\n");
	if (error == ERROR_ARG)
		printf("Wronng format of arguments\n");
}

void	init_mutexes(t_supper *data)
{
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
	pthread_mutex_init(&data->write_lock, NULL);
}

void	destroy_mutexes(t_supper *data)
{
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->meal_lock);
	pthread_mutex_destroy(&data->write_lock);
}

int	main(int argc, char **argv)
{
	t_supper	data;
	t_philo		philo_arr[BUFF];
	pthread_mutex_t	forks[BUFF];

	if (argc < 5 || argc > 6)
	{
		manage_errors(ERROR_ARG_NUM);
		return (ERROR_ARG_NUM);
	}
	if (check_args(argv, &data) != 0)
	{
		manage_errors(ERROR_ARG);
		return (ERROR_ARG);
	}
	init_forks(forks, &data);
	init_mutexes(&data);
	gather_philosophers(philo_arr, &data);
	destroy_forks(forks, &data);
	destroy_mutexes(&data);
}
