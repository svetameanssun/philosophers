#include "../include/philosophers.h"

int	uwait(int time, t_philo *philo)
{
	int	start;
	int	current_time;

	start = get_current_time();
	current_time = get_current_time();
	while (current_time - start < time)
	{
		if (somebody_is_dead(philo->data))
			return (1);
		usleep(100);
		current_time = get_current_time();
	}
	return (0);
}
void ms_sleep(size_t msec)
{
    usleep(msec * 1000);
}

size_t get_current_time(void)
{
    struct timeval time;
    size_t result_msec;

    gettimeofday(&time, NULL);
    result_msec = time.tv_sec*1000 + time.tv_usec/1000;
    return(result_msec); 
}

int somebody_is_dead(t_supper *data)
{
    int dead_flag;

    pthread_mutex_lock(&data->dead_lock);
    dead_flag = data->dead_flg;
    pthread_mutex_unlock(&data->dead_lock);
    return dead_flag;
}

void set_dead_flag(t_supper *data, int dead_flag)
{

    pthread_mutex_lock(&data->dead_lock);
    data->dead_flg = dead_flag;
    pthread_mutex_unlock(&data->dead_lock);
}


int print_msg(char *msg, t_philo *philo)
{
	if (!somebody_is_dead(philo->data))
    {
		safe_print(msg, philo);
        return (1);
    }
    return(0);
}
void safe_print(char *msg, t_philo *philo)
{
    size_t	time;

    pthread_mutex_lock(&philo->data->write_lock);
	time = get_current_time() - philo->start_time;
	printf("%zu %d %s\n", time, philo->id+1, msg);
    pthread_mutex_unlock(&philo->data->write_lock);
}

int action_sequence(t_philo *philo)
{
    print_msg("has taken a fork", philo);
    pthread_mutex_lock(philo->my_fork);
    if (philo->data->philos_nbr == 1)
    {
        pthread_mutex_unlock(philo->my_fork);
        pthread_mutex_unlock(&philo->data->meal_lock);
        uwait(philo->data->time_to_die, philo);
        set_dead_flag(philo->data, 1);
        printf("%zu %d died\n", get_current_time() - philo->start_time, philo->id+1);
        return(uwait(philo->data->time_to_die, philo));
    }
    pthread_mutex_lock(philo->other_fork);
    print_msg("has taken a fork", philo);
    print_msg("is eating", philo);
    philo->latest_meal_time = get_current_time();
    philo->meals_eaten++;
    ms_sleep(philo->data->time_to_eat);
    pthread_mutex_unlock(philo->my_fork);
    pthread_mutex_unlock(philo->other_fork);
    if (philo->meals_eaten == philo->data->meals_to_eat || somebody_is_dead(philo->data))
        return(1);
    print_msg("is sleeping", philo);
    ms_sleep(philo->data->time_to_sleep);
    print_msg("is thinking", philo);
    return (0);
}

void *routine(void *ref)
{
    t_philo *philo;

    philo = ref;
    if (philo->id % 2 != 0)
        uwait(1, philo);
    while(1)
    {
        if (action_sequence(philo) != 0)
            return (NULL);
    }
    return (philo); 
}
