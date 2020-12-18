#include "philo_two.h"

static int	get_fork(t_philosopher *man)
{
	if (sem_wait(g_block) != 0)
		return (1);
	if (sem_wait(g_forks) != 0)
		return (1);
	--(g_config.forks);
	if (print_log("has taken a fork!", man->number))
		return (1);
	if (sem_wait(g_forks) != 0)
		return (1);
	--(g_config.forks);
	if (print_log("has taken a fork!", man->number))
		return (1);
	if (sem_post(g_block) != 0)
		return (1);
	return (0);
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
	if (sem_post(g_forks) != 0)
		return (1);
	++(g_config.forks);
	if (sem_post(g_forks) != 0)
		return (1);
	++(g_config.forks);
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
	{
		g_config.exit = 1;
		return ((void *)0);
	}
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
