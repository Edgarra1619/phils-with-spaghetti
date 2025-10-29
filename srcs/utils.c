/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgribei <edgribei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:18:51 by edgribei          #+#    #+#             */
/*   Updated: 2025/10/29 15:43:06 by edgribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>

int	get_current_time(void)
{
	static int		starting_time;
	struct timeval	time;
	int				current;

	gettimeofday(&time, NULL);
	current = (time.tv_sec * 1000 + time.tv_usec / 1000);
	if (!starting_time)
		starting_time = current;
	return (current - starting_time);
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
