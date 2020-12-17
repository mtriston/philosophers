
#include "philo_one.h"

void monitor(void)
{
	struct timeval	time;
	int				i;

	while (g_config.iterations != 0)
	{
		i = 0;
		while (i < g_config.num_of_philo)
		{
			gettimeofday(&time, NULL);
			if ((time.tv_sec * 1000 + time.tv_usec / 1000 - g_philosophers[i].time_last_eating) >= g_config.time_to_die)
			{
				print_log("died", g_philosophers[i].number);
				return ;
			}
			++i;
		}
	}
}

int main(int argc, char **argv)
{
	int i;

	if (argc < 5 || argc > 7)
	{
		ft_putendl_fd("Error. Invalid arguments", 1);
		return (0);
	}
	initialization(argc, argv);
	i = 0;
	while (i < g_config.num_of_philo)
	{
		pthread_create(&g_threads[i], NULL, life_cycle, (void *)&g_philosophers[i]);
		++i;
	}
	monitor();
	return 0;
}
