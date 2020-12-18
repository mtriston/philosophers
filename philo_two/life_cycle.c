#include "philo_two.h"

static int	get_fork(t_philosopher *man)
{
	while (1)
	{
		if (!man->man_of_the_left->busy)
		{
			if (pthread_mutex_lock(&man->left_fork) != 0)
				return (1);
			man->busy = 1;
			if (print_log("has taken a fork!", man->number))
				return (1);
			if (pthread_mutex_lock(&man->right_fork) != 0)
				return (1);
			if (print_log("has taken a fork!", man->number))
				return (1);
			return (0);	
		}
	}
}

static int	eating(t_philosopher *man)
{
	struct timeval time;

	if (print_log("is eating!", man->number))
		return (1);
	if (gettimeofday(&time, NULL) != 0)
		return (1);
	man->time_last_eating = time.tv_sec * 1000 + time.tv_usec / 1000;
	if (usleep(g_config.eating * 1000) != 0)
		return (1);
	if (pthread_mutex_unlock(&man->right_fork) != 0)
		return (1);
	if (pthread_mutex_unlock(&man->left_fork) != 0)
		return (1);
	man->busy = 0;
	return (0);
}

static int	sleeping(t_philosopher *man)
{
		if (print_log("is sleeping!", man->number))
			return (1);
		if (usleep(g_config.sleeping * 1000) != 0)
			return (1);
		return (0);
}

void		*life_cycle(void *arg)
{
	t_philosopher	*man;

	man = (t_philosopher *)arg;
	if (pthread_detach(g_threads[man->number]) != 0)
		return (prepare_to_exit());
	while (man->iterations != 0)
	{
		if (get_fork(man) || eating(man) || sleeping(man) || \
								print_log("is thinking!", man->number))
		{
			g_config.exit = 1;
			return ((void *)0);
		}
		if (man->iterations != -1)
		{
			man->iterations -= 1;
			g_config.iterations -= 1;
		}
	}
	return ((void *)0);
}
