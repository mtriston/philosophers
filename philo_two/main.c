#include "philo_two.h"

void	*prepare_to_exit(void)
{
	int i;

	i = 0;
	while (i < g_config.num_of_philo)
	{
		pthread_mutex_destroy(&g_forks[i]);
		++i;
	}
	free(g_forks);
	free(g_philosophers);
	free(g_threads);
	return ((void *)0);
}

static int	monitor(void)
{
	struct timeval	time;
	int				i;

	while (g_config.iterations != 0 && g_config.exit == 0)
	{
		i = 0;
		while (i < g_config.num_of_philo)
		{
			if (gettimeofday(&time, NULL) != 0)
				return (1);
			if ((time.tv_sec * 1000 + time.tv_usec / 1000 - \
				g_philosophers[i].time_last_eating) >= g_config.time_to_die \
				&& g_philosophers[i].iterations != 0)
			{
				print_log("died", g_philosophers[i].number);
				return (0);
			}
			++i;
		}
	}
	return (0);
}

static int	check_args(int argc, char **argv)
{
	int i;
	int j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i] && argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (1);
			++j;
		}
		++i;
	}
	return (0);
}

int main(int argc, char **argv)
{
	if (argc < 5 || argc > 7 || check_args(argc, argv))
	{
		ft_putendl_fd("Error. Invalid arguments", 1);
		return (0);
	}
	if (initialization(argc, argv))
	{
		ft_putendl_fd("Fatal error.", 1);
		return (1);
	}
	if (monitor())
		ft_putendl_fd("Fatal error.", 1);
	prepare_to_exit();
	return (g_config.exit);
}
