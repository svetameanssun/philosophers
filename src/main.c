#include "../include/philosophers.h"

/*size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}*/

void init_mutexes(t_supper * data)
{
    pthread_mutex_init(&data->dead_lock, NULL);
    pthread_mutex_init(&data->meal_lock, NULL);
    pthread_mutex_init(&data->write_lock, NULL);
}

void destroy_mutexes(t_supper * data)
{
    pthread_mutex_destroy(&data->dead_lock);
    pthread_mutex_destroy(&data->meal_lock);
    pthread_mutex_destroy(&data->write_lock);
}

int main(int argc, char **argv)
{
    t_supper data;
    if (argc < 5 || argc > 6 || check_args(argv, &data) != 0)
        return(ERROR_ARG);
    t_philo philo_arr[data.philos_nbr];// create function, for norminette !
    pthread_mutex_t forks[data.philos_nbr];// create function, for norminette !
    init_forks(forks, &data);
    init_mutexes(&data);
    gather_philosophers(philo_arr, &data);
    destroy_forks(forks, &data);
    printf("HET\n");
    destroy_mutexes(&data);
    printf("ДА\n");
}