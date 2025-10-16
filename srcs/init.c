#include <stdlib.h>

#include <libft.h>
#include <philo.h>

int	init_mutexes(t_world *data)
{
	int	i;

	i = data->args[0] - 1;
	if (pthread_mutex_init(&data->printex, NULL))
		return (1);
	if (pthread_mutex_init(&data->state.lock, NULL))
		return (1);
	while (i >= 0)
	{
		if (pthread_mutex_init(&(data->forks[i]).lock, NULL))
		{
			pthread_mutex_destroy(&data->printex);
			while (i < data->args[1])
			{
				pthread_mutex_destroy(&(data->forks[i]).lock);
				i++;
			}
			return (1);
		}
		i--;
	}
	return (0);
}

void	fill_phils(t_world *data)
{
	int	i;

	i = data->args[0] - 1;
	while (i >= 0)
	{
		data->phils[i].args = data->args;
		data->phils[i].printex = &data->printex;
		data->phils[i].forks[0] = data->forks + i;
		data->phils[i].forks[1] = data->forks + ((i + 1) % data->args[0]);
		data->phils[i].index = i + 1;
		data->phils[i].state = &data->state;
		data->phils[i].times_eaten = 0;
		i--;
	}
}

int	init_phils(t_world *data)
{
	data->phils = ft_calloc(sizeof(t_philos), data->args[0]);
	if (!data->phils)
		return (1);
	data->forks = ft_calloc(sizeof(t_locked_int), data->args[0]);
	if (!data->forks)
	{
		free(data->phils);
		return (1);
	}
	if (init_mutexes(data))
	{
		free(data->phils);
		free(data->forks);
		return (1);
	}
	fill_phils(data);
	data->state.value = 0;
	return (0);
}
