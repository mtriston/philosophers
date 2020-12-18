#include "philo_two.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void		ft_putnbr_fd(int n, int fd)
{
	if (n <= -10)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(n / -10, fd);
		ft_putchar_fd((n % 10 * (-1)) + '0', fd);
	}
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(-n, fd);
	}
	else if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd(n % 10 + '0', fd);
	}
	else if (n < 10 && n >= 0)
		ft_putchar_fd(n + '0', fd);
}

void	ft_putendl_fd(char *s, int fd)
{
	unsigned i;

	i = 0;
	while (s[i])
		i++;
	write(fd, s, i);
	ft_putchar_fd('\n', fd);
}

int		ft_atoi(const char *nptr)
{
	int		i;
	long	num;
	int		sign;

	i = 0;
	num = 0;
	sign = 1;
	while (nptr[i] && (nptr[i] == ' ' || nptr[i] == '\t' || nptr[i] == '\n' || \
	nptr[i] == '\r' || nptr[i] == '\v' || nptr[i] == '\f'))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
		num = num * 10 + (nptr[i++] - '0');
	return ((int)(num * sign));
}

int 	print_log(char *message, int number)
{
	struct timeval time;

	if (sem_wait(g_print) != 0)
		return (1);
	if (gettimeofday(&time, NULL) != 0)
		return (1);
	ft_putnbr_fd(time.tv_sec * 1000 + time.tv_usec / 1000 - g_config.start, 1);
	ft_putchar_fd(' ', 1);
	ft_putnbr_fd(number + 1, 1);
	ft_putchar_fd(' ', 1);
	ft_putendl_fd(message, 1);
	if (sem_post(g_print) != 0)
		return (1);
	return (0);
}

