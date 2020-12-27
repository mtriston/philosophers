/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtriston <mtriston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 15:08:19 by mtriston          #+#    #+#             */
/*   Updated: 2020/12/27 15:08:39 by mtriston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void		*prepare_to_exit(void)
{
	int i;

	i = 0;
	while (i < g_config.num_of_philo)
		if (pthread_join(g_threads[i++], NULL) != 0)
			g_config.exit = 1;
	if (sem_close(g_forks) != 0 || sem_unlink(SEM_FORKS) != 0)
		g_config.exit = 1;
	if (sem_close(g_print) != 0 || sem_unlink(SEM_PRINT) != 0)
		g_config.exit = 1;
	if (sem_close(g_waiter) != 0 || sem_unlink(SEM_WAITER) != 0)
		g_config.exit = 1;
	if (sem_close(g_block) != 0 || sem_unlink(SEM_BLOCK) != 0)
		g_config.exit = 1;
	free(g_philosophers);
	free(g_threads);
	return ((void *)0);
}

static int	is_philo_dead(t_philosopher *man)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		return (1);
	if (sem_wait(g_block) != 0)
		return (1);
	if ((time.tv_sec * 1000 + time.tv_usec / 1000 - \
				man->time_last_eating) >= g_config.time_to_die \
				&& man->iterations != 0)
	{
		if (print_log("died", man->number))
			return (1);
		g_config.someone_died = 1;
	}
	if (sem_post(g_block) != 0)
		return (1);
	return (0);
}

static int	monitor(void)
{
	int				i;

	while (g_config.iterations != 0 && !g_config.exit && \
											!g_config.someone_died)
	{
		i = 0;
		while (i < g_config.num_of_philo)
		{
			if (is_philo_dead(&g_philosophers[i]) == 1)
				g_config.exit = 1;
			++i;
			usleep(50);
		}
	}
	return (g_config.exit);
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

int			main(int argc, char **argv)
{
	if (argc < 5 || argc > 7 || check_args(argc, argv))
	{
		ft_putendl_fd("Error. Invalid arguments", 1);
		return (1);
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
