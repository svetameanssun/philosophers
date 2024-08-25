/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stitovsk <stitovsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 18:01:12 by stitovsk          #+#    #+#             */
/*   Updated: 2024/08/25 19:59:48 by stitovsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	uwait(int time, t_philo *philo)
{
	int	start;
	int	current_time;

	start = get_current_time();
	current_time = get_current_time();
	while (current_time - start < time)
	{
		if (smbd_dead(philo->data))
		{
			return (1);
		}
		usleep(100);
		current_time = get_current_time();
	}
	return (0);
}

void	ms_sleep(size_t msec)
{
	usleep(msec * 1000);
}

size_t	get_current_time(void)
{
	struct timeval	time;
	size_t			result_msec;

	gettimeofday(&time, NULL);
	result_msec = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (result_msec);
}

int	print_msg(char *msg, t_philo *philo)
{
	if (!smbd_dead(philo->data))
	{
		safe_print(msg, philo);
		return (1);
	}
	return (0);
}

void	safe_print(char *msg, t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(&philo->data->write_lock);
	time = get_current_time() - philo->start_time;
	printf("%zu %d %s\n", time, philo->id + 1, msg);
	if (philo->data->dead_flg == 1)
	{
		return ;
	}
	pthread_mutex_unlock(&philo->data->write_lock);
}
