/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtriston <mtriston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 22:42:56 by mtriston          #+#    #+#             */
/*   Updated: 2020/12/16 20:44:51 by mtriston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static int forks_init(void)
{
	int i;

	i = 0;
	g_forks = malloc(sizeof(pthread_mutex_t) * g_config.num_of_philo);
	if (g_forks == NULL)
		return (1);
	while (i < g_config.num_of_philo)
	{
		if (pthread_mutex_init(&g_forks[i], NULL) != 0)
			return (1);
		++i;
	}
	return (0);
}

static int	threads_init(void)
{
	int i;

	i = 0;
	g_threads = malloc(sizeof(pthread_mutex_t) * g_config.num_of_philo);
	if (g_threads == NULL)
		return (1);
	while (i < g_config.num_of_philo)
	{
		if (pthread_create(&g_threads[i], NULL, life_cycle,\
										(void *)&g_philosophers[i]) != 0)
			return (1);
		++i;
	}
	return (0);
}

static int	philosophers_init(void)
{
	int	i;

	i = 0;
	g_philosophers = malloc(sizeof(t_philosopher) * g_config.num_of_philo);
	if (g_philosophers == NULL)
		return (1);
	while (i < g_config.num_of_philo)
	{
		g_philosophers[i].number = i;
		g_philosophers[i].time_last_eating = g_config.start;
		g_philosophers[i].left_fork = i == 0 ? \
							g_forks[g_config.num_of_philo - 1] : g_forks[i - 1];
		g_philosophers[i].right_fork = i == (g_config.num_of_philo - 1) ? \
									   				g_forks[0] : g_forks[i + 1];
		g_philosophers[i].busy = 0;
		g_philosophers[i].man_of_the_left = i == (g_config.num_of_philo - 1) ? \
									&g_philosophers[0] : &g_philosophers[i + 1];
		g_philosophers[i].iterations = g_config.iterations;
		++i;
	}
	return (0);
}

static int	config_init(int argc, char **argv)
{

	struct		timeval time;

	if (gettimeofday(&time, NULL) != 0)
		return (1);
	g_config.start = time.tv_sec * 1000 + time.tv_usec / 1000;
	g_config.num_of_philo = ft_atoi(argv[1]);
	g_config.time_to_die = ft_atoi(argv[2]);
	g_config.eating = ft_atoi(argv[3]);
	g_config.sleeping = ft_atoi(argv[4]);
	g_config.iterations = argc == 6 ? ft_atoi(argv[5]) : -1;
	g_config.exit = 0;
	return (0);
}

int initialization(int argc, char **argv)
{	
	if (config_init(argc, argv))
		return (1);
	if (forks_init())
		return (1);
	if (philosophers_init())
		return (1);
	g_config.iterations = g_config.iterations == -1 ? \
			g_config.iterations : g_config.iterations * g_config.num_of_philo;
	if (threads_init())
		return (1);
	return (0);
}
