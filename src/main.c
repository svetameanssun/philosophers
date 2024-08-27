/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stitovsk <stitovsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 20:55:24 by stitovsk          #+#    #+#             */
/*   Updated: 2024/08/27 17:51:55 by stitovsk         ###   ########.fr       */
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
	pthread_mutex_init(&data->aux_lock, NULL);
}

void	destroy_mutexes(t_supper *data)
{
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->meal_lock);
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->aux_lock);
}

int	main(int argc, char **argv)
{
	t_supper		data;
	t_philo			philo_arr[BUFF];
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
	/*if (philo_arr->data->dead_flg == 1)
		pthread_mutex_unlock(&philo_arr->data->write_lock);*/
	destroy_forks(forks, &data);
	destroy_mutexes(&data);
}
