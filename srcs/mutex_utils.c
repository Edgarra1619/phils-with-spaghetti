/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgribei <edgribei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:18:46 by edgribei          #+#    #+#             */
/*   Updated: 2025/10/29 15:19:25 by edgribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

#include <pthread.h>

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
