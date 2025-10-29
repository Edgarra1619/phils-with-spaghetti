/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgribei <edgribei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:23:50 by edgribei          #+#    #+#             */
/*   Updated: 2025/10/29 15:27:51 by edgribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#include <philo.h>

int	update_last_eaten(t_philos *data)
{
	const int	tmp = get_current_time();

	set_unlock_int(&data->times_eaten,
		check_unlock_int(&data->times_eaten) + 1);
	set_unlock_int(&data->last_eaten, tmp);
	return (tmp);
}

void	philosopher_eat(t_philos *data)
{
	data->forks[0]->value = 0;
	if (check_lock_int(data->printex))
	{
		printf("%d %d has taken a fork\n", get_current_time(), data->index);
		if (data->forks[0] == data->forks[1])
		{
			pthread_mutex_unlock(&data->forks[0]->lock);
			pthread_mutex_unlock(&data->printex->lock);
			usleep(1000 * (data->args[1] + 10));
			return ;
		}
		pthread_mutex_lock(&data->forks[1]->lock);
		printf("%d %d is eating\n", update_last_eaten(data), data->index);
		pthread_mutex_unlock(&data->printex->lock);
		usleep(1000 * data->args[2]);
		pthread_mutex_unlock(&data->forks[1]->lock);
	}
	else
		pthread_mutex_unlock(&data->printex->lock);
	pthread_mutex_unlock(&data->forks[0]->lock);
}

void	try_eat(t_philos *data)
{
	while (check_unlock_int(data->printex))
	{
		if (check_lock_int(data->forks[0]) == data->index)
		{
			philosopher_eat(data);
			return ;
		}
		pthread_mutex_unlock(&data->forks[0]->lock);
		usleep(1);
	}
}

void	sleep_philo(t_philos *data)
{
	if (check_lock_int(data->printex))
	{
		printf("%d %d is sleeping\n", get_current_time(), data->index);
		pthread_mutex_unlock(&data->printex->lock);
		usleep(1000 * data->args[3]);
	}
	else
		pthread_mutex_unlock(&data->printex->lock);
}

void	*start_philo(t_philos *data)
{
	while (check_unlock_int(data->printex))
	{
		try_eat(data);
		sleep_philo(data);
	}
	return (0);
}
