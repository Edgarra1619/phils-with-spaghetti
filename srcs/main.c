#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#include <libft.h>
#include <parse.h>
#include <philo.h>

void	*start_philo(void *data);
int	init_phils(t_world *data);

void	*threadin(t_world *data)
{
	printf("multithreading\n");
	pthread_mutex_lock(&data->printex);
	printf("mutexing\n");
	return (NULL);
}

int	main(__attribute__((unused)) int argc,
		 char **argv)
{
	t_world	data;

	data.args[4] = -1;
	if (parse_input(argv + 1, data.args))
		return (1);
	if (init_phils(&data))
		return (1);
	data.forks->value = 1;
	pthread_create(&data.phils->thread, NULL, start_philo, data.phils);
	usleep(1000000);
	pthread_detach(data.phils->thread);
	free(data.phils);
	free(data.forks);
}
