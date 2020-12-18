/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtriston <mtriston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 22:37:54 by mtriston          #+#    #+#             */
/*   Updated: 2020/12/18 20:55:00 by mtriston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_PHILO_TWO_H
# define PHILOSOPHERS_PHILO_TWO_H

# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <fcntl.h>
# define SEM_FORKS "/sem_forks"
# define SEM_PRINT "/sem_print"
# define SEM_BLOCK "/sem_block"

typedef struct				s_philosopher
{
	int 					number;
	long					time_last_eating;
	int 					iterations;
}							t_philosopher;

typedef struct		s_config
{
	int 			num_of_philo;
	int 			eating;
	int 			sleeping;
	int 			time_to_die;
	long 			start;
	int 			iterations;
	int				exit;
	int 			forks;
}					t_config;

t_philosopher		*g_philosophers;
pthread_t			*g_threads;
sem_t				*g_forks;
sem_t				*g_print;
sem_t				*g_block;
t_config			g_config;

void	*life_cycle(void *arg);
int		print_log(char *message, int number);
int		ft_atoi(const char *nptr);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putendl_fd(char *s, int fd);
int		initialization(int argc, char **argv);
void	*prepare_to_exit(void);


#endif
