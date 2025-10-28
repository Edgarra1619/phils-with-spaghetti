#include <stdio.h>
#include <unistd.h>
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
		if (check_unlock_int(&data->phils[i].times_eaten) <= data->args[4])
			return (0);
		i++;
	}
	return (1);
}

void	*death_checker_loop(t_world *data)
{
	int	i;
	int	tmp;

	i = 0;
	while (check_unlock_int(&data->printex))
	{
		i = (i + 1) % data->args[0];
		tmp = get_current_time();
		if (tmp -
			check_unlock_int(&data->phils[i].last_eaten) > data->args[1])
		{
			pthread_mutex_lock(&data->printex.lock);
			data->printex.value = 0;
			printf("%d %d died\n", get_current_time(), i + 1);
			pthread_mutex_unlock(&data->printex.lock);
			break;
		}
		if (check_eat_count(data))
		{
			set_unlock_int(&data->printex, 0);
			break;
		}
		usleep(1);
	}
	return (NULL);
}

void	fork_giver_loop(t_world *data)
{
	int	i;
	int	offset;
	int	tmp;

	i = 0;
	offset = 0;
	while (check_unlock_int(&data->printex))
	{
		usleep(1);
		tmp = i + offset;
		if (check_unlock_int(&(data->forks[(tmp + 1) % data->args[0]])))
			continue ;
		if (check_unlock_int(&(data->forks[(tmp + data->args[0] - 1) % data->args[0]])))
			continue ;
		set_unlock_int(&(data->forks[tmp % data->args[0]]), tmp % data->args[0] + 1);
		i += 2;
		if (i > data->args[0] - 2)
		{
			offset = (offset + 1) % data->args[0];
			i = 0;
		}
	}
}

int	main(__attribute__((unused)) int argc,
		 char **argv)
{
	t_world	data;
	int		i;

	data.args[4] = -1;
	if (parse_input(argv + 1, data.args))
		return (1);
	if (init_phils(&data))
		return (1);
	pthread_create(&data.death_checker, NULL,
			(void*(*)(void*))death_checker_loop, &data);
	i = -1;
	while (++i < data.args[0])
		pthread_create(&data.phils[i].thread, NULL,
				(void*(*)(void*))start_philo, (void*) (data.phils + i));
	fork_giver_loop(&data);
	i = -1;
	while (++i < data.args[0])
		pthread_join(data.phils[i].thread, NULL);
	pthread_join(data.death_checker, NULL);
	free_data(&data, 0);
}
