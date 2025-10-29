/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgribei <edgribei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:19:04 by edgribei          #+#    #+#             */
/*   Updated: 2025/10/29 15:19:13 by edgribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philo.h>

#include <pthread.h>
#include <stdlib.h>

int	init_phil_mutexes(t_philos *phil)
{
	if (pthread_mutex_init(&phil->forks[0]->lock, NULL))
		return (1);
	if (pthread_mutex_init(&phil->last_eaten.lock, NULL))
	{
		pthread_mutex_destroy(&phil->forks[0]->lock);
		return (1);
	}
	if (pthread_mutex_init(&phil->last_eaten.lock, NULL))
	{
		pthread_mutex_destroy(&phil->forks[0]->lock);
		pthread_mutex_destroy(&phil->last_eaten.lock);
		return (1);
	}
	return (0);
}

int	init_mutexes(t_world *data)
{
	int	i;

	i = data->args[0] - 1;
	if (pthread_mutex_init(&data->printex.lock, NULL))
		return (1);
	while (i >= 0)
	{
		if (init_phil_mutexes(data->phils + i))
		{
			free_data(data, i);
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
		data->phils[i].printex = &(data->printex);
		data->phils[i].forks[0] = data->forks + i;
		data->phils[i].forks[1] = data->forks + ((i + 1) % data->args[0]);
		data->phils[i].index = i + 1;
		data->phils[i].times_eaten.value = 0;
		data->phils[i].last_eaten.value = 0;
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
	fill_phils(data);
	if (init_mutexes(data))
		return (1);
	data->printex.value = 1;
	return (0);
}
