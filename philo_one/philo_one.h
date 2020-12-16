/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtriston <mtriston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 22:37:54 by mtriston          #+#    #+#             */
/*   Updated: 2020/12/15 22:16:05 by mtriston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_PHILO_ONE_H
# define PHILOSOPHERS_PHILO_ONE_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct				s_philosopher
{
	unsigned				number;
	long					time_last_eating;
	pthread_mutex_t			left_fork;
	pthread_mutex_t			right_fork;
	int 					busy;
	int 					iterations;
	struct s_philosopher	*man_of_the_left;
}							t_philosopher;

typedef struct		s_config
{
	int 			num_of_philo;
	int 			eating;
	int 			sleeping;
	int 			time_to_die;
	long 			start;
	int 			iterations;
}					t_config;

t_philosopher		*g_philosophers;
pthread_t			*g_threads;
pthread_mutex_t		*g_forks;
pthread_mutex_t		g_print;
t_config			g_config;

int		ft_atoi(const char *nptr);
void	initialization(int argc, char **argv);


#endif
