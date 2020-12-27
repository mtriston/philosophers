/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtriston <mtriston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 21:20:48 by mtriston          #+#    #+#             */
/*   Updated: 2020/12/27 18:03:44 by mtriston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_PHILO_THREE_H
# define PHILOSOPHERS_PHILO_THREE_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <semaphore.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# define SEM_FORKS "/sem_forks"
# define SEM_PRINT "/sem_print"
# define SEM_WAITER "/sem_waiter"
# define SEM_BLOCK "/sem_block"
# define DEAD 2

typedef struct		s_philosopher
{
	int				number;
	long			time_last_eating;
	int				iterations;
	pthread_t		monitor;
}					t_philosopher;

typedef struct		s_config
{
	int				num_of_philo;
	int				in_process;
	int				eating;
	int				sleeping;
	int				time_to_die;
	long			start;
	int				iterations;
}					t_config;

t_philosopher		*g_philosophers;
pid_t				*g_processes;
sem_t				*g_forks;
sem_t				*g_print;
sem_t				*g_waiter;
sem_t				*g_block;
t_config			g_config;

int					life_cycle(t_philosopher *man);
int					print_log(char *message, int number);
int					ft_atoi(const char *nptr);
void				ft_putchar_fd(char c, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putendl_fd(char *s, int fd);
int					initialization(int argc, char **argv);

#endif
