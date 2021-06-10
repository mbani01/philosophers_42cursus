/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani <mbani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 12:06:57 by mbani             #+#    #+#             */
/*   Updated: 2021/06/07 12:08:54 by mbani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

long	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	res;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while ((str[i] != '\0') && (str[i] <= '9' && str[i] >= '0'))
	{
		res = ((res * 10) + (str[i] - 48));
		if (res > 2147483648 && sign == -1)
			return (0);
		else if (res > 2147483647 && sign == 1)
			return (-1);
		i++;
	}
	return (res * sign);
}

static	void	ft_print(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(long n, int fd)
{
	unsigned long	new_nb;

	new_nb = n;
	if (n < 0)
	{
		ft_print('-', fd);
		new_nb = n * -1;
	}
	if (new_nb > 9)
	{
		ft_putnbr_fd(new_nb / 10, fd);
		ft_print((new_nb % 10) + '0', fd);
	}
	if (new_nb <= 9)
	{
		ft_print((new_nb) + '0', fd);
	}
}

static	void	ft_pprint(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
	{
		while (*s != '\0')
		{
			ft_pprint(*s, fd);
			s++;
		}
	}
}
