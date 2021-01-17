/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtriston <mtriston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 18:10:43 by mtriston          #+#    #+#             */
/*   Updated: 2021/01/14 21:12:45 by mtriston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int	prepare_to_exit(void)
{
	int i;

	i = 0;
	while (i < g_config.num_of_philo)
		kill(g_processes[i++], SIGKILL);
	if (sem_close(g_forks) != 0 || sem_unlink(SEM_FORKS) != 0)
		return (1);
	if (sem_close(g_print) != 0 || sem_unlink(SEM_PRINT) != 0)
		return (1);
	if (sem_close(g_waiter) != 0 || sem_unlink(SEM_WAITER) != 0)
		return (1);
	if (sem_close(g_block) != 0 || sem_unlink(SEM_BLOCK) != 0)
		return (1);
	free(g_philosophers);
	free(g_processes);
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
				return (EXIT_FAILURE);
			++j;
		}
		++i;
	}
	return (EXIT_SUCCESS);
}

static int	monitoring_processes(void)
{
	int i;
	int status;

	while (g_config.in_process > 0)
	{
		i = 0;
		while (i < g_config.num_of_philo)
		{
			waitpid(g_processes[i], &status, WNOHANG);
			if (WIFEXITED(status))
				status = WEXITSTATUS(status);
			if (status == EXIT_SUCCESS)
				g_config.in_process -= 1;
			else if (status == DEAD)
				return (0);
			else if (status == EXIT_FAILURE)
				return (1);
			++i;
		}
	}
	return (0);
}

int			main(int argc, char **argv)
{
	if (argc < 5 || argc > 7 || check_args(argc, argv))
	{
		ft_putendl_fd("Error. Invalid arguments", 1);
		return (EXIT_FAILURE);
	}
	if (initialization(argc, argv) || monitoring_processes() \
											|| prepare_to_exit())
	{
		ft_putendl_fd("Fatal error.", 1);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
