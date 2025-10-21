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
	t_locked_int		*printex;
	t_locked_int		*forks[2];
	const int			*args;
	int					index;
	t_locked_int		last_eaten;
	t_locked_int		times_eaten;
} t_philos;

typedef struct	s_world
{
	t_locked_int	printex;
	t_locked_int	*forks;
	t_philos		*phils;
	int				args[5];
	t_locked_int	state;
} t_world;

int		get_current_time(void);

int	check_unlock_int(t_locked_int *check);
int	set_unlock_int(t_locked_int *set, int value);
int	check_lock_int(t_locked_int *check);

#endif
