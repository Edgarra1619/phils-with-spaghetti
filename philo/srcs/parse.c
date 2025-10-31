/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgribei <edgribei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:17:49 by edgribei          #+#    #+#             */
/*   Updated: 2025/10/29 15:17:51 by edgribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <philo.h>

int	parse_input(char **argv, int *args)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (!argv[i])
			return (i != 4);
		if (safe_atoi(argv[i], args + i))
			return (1);
		if (args[i] < 0)
			return (1);
		i++;
	}
	return (!!argv[i]);
}
