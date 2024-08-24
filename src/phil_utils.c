/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svetameanssun <svetameanssun@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:26:45 by svetameanss       #+#    #+#             */
/*   Updated: 2024/08/24 16:26:46 by svetameanss      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ft_isspace(int c)
{
	return ((c == ' ') || (c >= 9 && c <= 13));
}

int	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (ERROR_NUMBER);
		i++;
	}
	return (0);
}

int	ft_atoi(char *str)
{
	if (is_number(str) != 0)
	{
		return (ERROR_ATOI);
	}
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (ft_isspace(str[i]) != 0)
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10;
		res = res + str[i] - '0';
		i++;
	}
	return (res);
}

int	check_args(char **argv, t_supper *data)
{
	data->dead_flg = 0;
	data->meals_to_eat = 0;
	data->philos_full = 0;
	data->philos_nbr = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (data->philos_nbr < 0 || data->time_to_die < 0
		|| data->time_to_eat < 0 || data->time_to_sleep < 0)
		return (ERROR_ARG);
	if (argv[5])
	{
		data->meals_to_eat = ft_atoi(argv[5]);
		if (data->meals_to_eat == -1)
			return (ERROR_ARG);
	}
	return (0);
}
