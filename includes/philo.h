#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>

typedef struct	s_locked_int
{
	pthread_mutex_t	lock;
	int				value;
} t_locked_int;

typedef struct	s_philos
{
	pthread_t			thread;
	pthread_mutex_t		*printex;
	t_locked_int		*forks[2];
	const int			*args;
	t_locked_int		*state;
	int					index;
	int					last_eaten;
	int					times_eaten;
} t_philos;

typedef struct	s_world
{
	pthread_mutex_t	printex;
	t_locked_int	*forks;
	t_philos		*phils;
	int				args[5];
	t_locked_int	state;
} t_world;

int		get_current_time(void);

#endif
