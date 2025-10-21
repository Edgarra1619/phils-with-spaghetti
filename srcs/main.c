#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#include <libft.h>
#include <parse.h>
#include <philo.h>

void	*start_philo(void *data);
int	init_phils(t_world *data);

int	check_eat_count(t_world *data)
{
	int	i;

	if (data->args[4] == -1)
		return (0);
	i = 0;
	while (i < data->args[0])
	{
		if (check_unlock_int(&data->phils[i].times_eaten) >= data->args[4])
			return (0);
		i++;
	}
	return (1);
}

void	*death_checker(t_world *data)
{
	int	i;

	i = 0;
	while (1)
	{
		i = (i + 1) % data->args[0];
		if (get_current_time() -
			check_unlock_int(&data->phils[i].last_eaten) > data->args[1]
			|| check_eat_count(data))
		{
			set_unlock_int(&data->printex, 0);
			break;
		}
		usleep(1);
	}
	return (NULL);
}

int	main(__attribute__((unused)) int argc,
		 char **argv)
{
	t_world	data;

	data.args[4] = -1;
	if (parse_input(argv + 1, data.args))
		return (1);
	//TODO rework init phils
	if (init_phils(&data))
		return (1);
	data.forks->value = 1;
	pthread_create(&data.phils->thread, NULL, start_philo, data.phils);
	usleep(1000000);
	pthread_detach(data.phils->thread);
	free(data.phils);
	free(data.forks);
}
