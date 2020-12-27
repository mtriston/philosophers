/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtriston <mtriston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 18:04:07 by mtriston          #+#    #+#             */
/*   Updated: 2020/12/27 18:05:00 by mtriston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int	get_fork(t_philosopher *man)
{
	if (sem_wait(g_waiter) != 0)
		return (1);
	if (sem_wait(g_forks) != 0)
		return (1);
	if (print_log("has taken a fork!", man->number))
		return (1);
	if (sem_wait(g_forks) != 0)
		return (1);
	if (print_log("has taken a fork!", man->number))
		return (1);
	if (sem_post(g_waiter) != 0)
		return (1);
	return (0);
}

static int	eating(t_philosopher *man)
{
	struct timeval time;

	if (sem_wait(g_block) != 0)
		return (1);
	if (print_log("is eating!", man->number))
		return (1);
	if (gettimeofday(&time, NULL) != 0)
		return (1);
	man->time_last_eating = time.tv_sec * 1000 + time.tv_usec / 1000;
	if (sem_post(g_block) != 0)
		return (1);
	if (usleep(g_config.eating * 1000) != 0)
		return (1);
	if (sem_post(g_forks) != 0)
		return (1);
	if (sem_post(g_forks) != 0)
		return (1);
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

void		*monitor(void *arg)
{
	struct timeval	time;
	t_philosopher	*man;

	man = (t_philosopher *)arg;
	while (man->iterations != 0)
	{
		if (sem_wait(g_block) != 0)
			exit(EXIT_FAILURE);
		if (gettimeofday(&time, NULL) != 0)
			exit(EXIT_FAILURE);
		if ((time.tv_sec * 1000 + time.tv_usec / 1000 - \
			man->time_last_eating) >= g_config.time_to_die \
			&& man->iterations != 0)
		{
			print_log("died", man->number);
			sem_wait(g_print);
			exit(DEAD);
		}
		if (sem_post(g_block) != 0)
			exit(EXIT_FAILURE);
		usleep(50);
	}
	exit(EXIT_SUCCESS);
}

int			life_cycle(t_philosopher *man)
{
	if (pthread_create(&man->monitor, NULL, monitor,\
										(void *)man) != 0)
		exit(EXIT_FAILURE);
	if (pthread_detach(man->monitor) != 0)
		exit(EXIT_FAILURE);
	while (man->iterations != 0)
	{
		if (get_fork(man) || eating(man) || sleeping(man) || \
								print_log("is thinking!", man->number))
			exit(EXIT_FAILURE);
		if (man->iterations != -1)
			man->iterations -= 1;
	}
	exit(EXIT_SUCCESS);
}
