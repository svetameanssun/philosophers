#include "../include/philosophers.h"

int check_args(char **argv, t_supper *data)
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
        return(ERROR_ARG);
    if (argv[5])
    {
        data->meals_to_eat = ft_atoi(argv[5]);
        if (data->meals_to_eat == -1)
            return(ERROR_ARG);
    }
    return(0);
}