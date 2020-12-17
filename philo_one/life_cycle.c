#include "philo_one.h"

static void	get_fork(t_philosopher *man)
{
	while (1)
	{
		if (!man->man_of_the_left->busy)
		{
			pthread_mutex_lock(&man->left_fork);
			man->busy = 1;
			print_log("has taken a fork!", man->number);
			pthread_mutex_lock(&man->right_fork);
			print_log("has taken a fork!", man->number);
			break;
		}
	}
}

static void	eating(t_philosopher *man)
{
	struct timeval time;

	print_log("is eating!", man->number);
	gettimeofday(&time, NULL);
	man->time_last_eating = time.tv_sec * 1000 + time.tv_usec / 1000;
	usleep(g_config.eating * 1000);
	pthread_mutex_unlock(&man->right_fork);
	pthread_mutex_unlock(&man->left_fork);
	man->busy = 0;
}

void		*life_cycle(void *arg)
{
	t_philosopher	*man;

	man = (t_philosopher *)arg;
	pthread_detach(g_threads[man->number]);
	while (man->iterations != 0)
	{
		get_fork(man);
		eating(man);
		print_log("is sleeping!", man->number);
		usleep(g_config.sleeping * 1000);
		print_log("is thinking!", man->number);
		if (man->iterations != -1)
		{
			man->iterations -= 1;
			g_config.iterations -= 1;
		}
	}
	return ((void *)0);
}
