#include <philo.h>

#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>

int	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec % 1000 * 1000 + time.tv_usec / 1000);
}

int	set_unlock_int(t_locked_int *set, int value)
{
	int	return_value;

	pthread_mutex_lock(&set->lock);
	set->value = value;
	return_value = value;
	pthread_mutex_unlock(&set->lock);
	return (return_value);
}

int	check_lock_int(t_locked_int *check)
{
	int	return_value;

	pthread_mutex_lock(&check->lock);
	return_value = check->value;
	return (return_value);
}

int	check_unlock_int(t_locked_int *check)
{
	int	return_value;

	pthread_mutex_lock(&(check->lock));
	return_value = check->value;
	pthread_mutex_unlock(&check->lock);
	return (return_value);
}

void	free_philosopher(t_philos *phil)
{
	pthread_mutex_destroy(&phil->times_eaten.lock);
	pthread_mutex_destroy(&phil->last_eaten.lock);
	pthread_mutex_destroy(&phil->forks[0]->lock);
}

void	free_data(t_world *data, int first_phil)
{
	int	i;

	pthread_mutex_destroy(&data->printex.lock);
	i = first_phil;
	while (i < data->args[0])
	{
		free_philosopher(data->phils + i);
		i++;
	}
	free(data->phils);
	free(data->forks);
}
