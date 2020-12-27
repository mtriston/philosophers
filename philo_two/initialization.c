/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtriston <mtriston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 22:42:56 by mtriston          #+#    #+#             */
/*   Updated: 2020/12/27 15:08:10 by mtriston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static int	semaphore_init(void)
{
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_WAITER);
	sem_unlink(SEM_BLOCK);
	g_forks = sem_open(SEM_FORKS, O_CREAT, 0644, g_config.num_of_philo);
	if (g_forks == SEM_FAILED)
		return (1);
	g_print = sem_open(SEM_PRINT, O_CREAT, 0644, 1);
	if (g_print == SEM_FAILED)
		return (1);
	g_waiter = sem_open(SEM_WAITER, O_CREAT, 0644, 1);
	if (g_waiter == SEM_FAILED)
		return (1);
	g_block = sem_open(SEM_BLOCK, O_CREAT, 0644, 1);
	if (g_block == SEM_FAILED)
		return (1);
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
		g_philosophers[i].iterations = g_config.iterations;
		++i;
	}
	return (0);
}

static int	config_init(int argc, char **argv)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		return (1);
	g_config.start = time.tv_sec * 1000 + time.tv_usec / 1000;
	g_config.num_of_philo = ft_atoi(argv[1]);
	g_config.time_to_die = ft_atoi(argv[2]);
	g_config.eating = ft_atoi(argv[3]);
	g_config.sleeping = ft_atoi(argv[4]);
	g_config.iterations = argc == 6 ? ft_atoi(argv[5]) : -1;
	g_config.exit = 0;
	g_config.someone_died = 0;
	return (0);
}

int			initialization(int argc, char **argv)
{
	if (config_init(argc, argv))
		return (1);
	if (philosophers_init())
		return (1);
	if (semaphore_init())
		return (1);
	g_config.iterations = g_config.iterations == -1 ? \
			g_config.iterations : g_config.iterations * g_config.num_of_philo;
	if (threads_init())
		return (1);
	return (0);
}
