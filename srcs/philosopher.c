#include <sys/time.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#include <philo.h>

void	try_eat(t_philos *data)
{
	pthread_mutex_lock(&(data->state->lock));
	while (!data->state->value)
	{
		pthread_mutex_unlock(&(data->state->lock));
		pthread_mutex_lock(&data->forks[0]->lock);
		if (data->forks[0]->value == data->index)
		{
			data->last_eaten = get_current_time();
			data->forks[0]->value = 0;
			pthread_mutex_lock(data->printex);
			printf("%d %d has taken a fork\n", data->last_eaten, data->index);
			pthread_mutex_lock(&data->forks[1]->lock);
			printf("%d %d is eating\n", data->last_eaten, data->index);
			pthread_mutex_unlock(data->printex);
			usleep(1000 * data->args[2]);
			pthread_mutex_unlock(&data->forks[0]->lock);
			pthread_mutex_unlock(&data->forks[1]->lock);
			return ;
		}
		pthread_mutex_unlock(&data->forks[0]->lock);
		usleep(1);
		pthread_mutex_lock(&(data->state->lock));
	}
	pthread_mutex_unlock(&(data->state->lock));
}

void	sleep_philo(t_philos *data)
{
	pthread_mutex_lock(data->printex);
	printf("%d %d is sleeping\n", get_current_time(), data->index);
	pthread_mutex_unlock(data->printex);
	usleep(1000 * data->args[3]);
}

void	*start_philo(t_philos *data)
{
	pthread_mutex_lock(&(data->state->lock));
	while (!data->state->value)
	{
		pthread_mutex_unlock(&(data->state->lock));
		try_eat(data);
		pthread_mutex_lock(&(data->state->lock));
		if (data->state->value)
			break ;
		pthread_mutex_unlock(&(data->state->lock));
		sleep_philo(data);
		pthread_mutex_lock(&(data->state->lock));
	}
	return (0);
}
