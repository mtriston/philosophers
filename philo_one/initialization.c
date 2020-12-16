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

#include "philo_one.h"

static void forks_init(void)
{
	unsigned i;

	i = 0;
	g_forks = malloc(sizeof(pthread_mutex_t) * g_config.num_of_philo);
	while (i < g_config.num_of_philo)
	{
		pthread_mutex_init(&g_forks[i], NULL);
		++i;
	}
}

static void	philosophers_init(void)
{
	unsigned	i;

	i = 0;
	g_philosophers = malloc(sizeof(t_philosopher) * g_config.num_of_philo);
	while (i < g_config.num_of_philo)
	{
		g_philosophers[i].number = i;
		g_philosophers[i].time_last_eating = g_config.start;
		g_philosophers[i].left_fork = i == 0 ? g_forks[g_config.num_of_philo - 1] : g_forks[i - 1];
		g_philosophers[i].right_fork = i == (g_config.num_of_philo - 1) ? g_forks[0] : g_forks[i + 1];
		g_philosophers[i].busy = 0;
		g_philosophers[i].man_of_the_left = i == (g_config.num_of_philo - 1) ? &g_philosophers[0] : &g_philosophers[i + 1];
		g_philosophers->iterations = g_config.iterations;
		++i;
	}
}

static void config_init(int argc, char **argv)
{

	struct		timeval time;

	gettimeofday(&time, NULL);
	g_config.start = time.tv_sec * 1000 + time.tv_usec / 1000;
	g_config.num_of_philo = ft_atoi(argv[1]);
	g_config.time_to_die = ft_atoi(argv[2]);
	g_config.eating = ft_atoi(argv[3]);
	g_config.sleeping = ft_atoi(argv[4]);
	g_config.iterations = argc == 6 ? ft_atoi(argv[5]) : -1;
}

void initialization(int argc, char **argv)
{
	g_threads = malloc(sizeof(pthread_mutex_t) * g_config.num_of_philo);
	config_init(argc, argv);
	forks_init();
	philosophers_init();
	g_config.iterations = g_config.iterations == -1 ? g_config.iterations : g_config.iterations * g_config.num_of_philo;
}