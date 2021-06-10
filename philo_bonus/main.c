/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani <mbani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 14:42:54 by mbani             #+#    #+#             */
/*   Updated: 2021/06/08 14:03:12 by mbani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	ft_logger(int state, long time, int id, t_philo *philo)
{
	sem_wait(philo->logger);
	ft_putnbr_fd(time - philo->time, 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(id, 1);
	if (state == 1)
		ft_putstr_fd(" \x1B[32mis eating\x1B[0m\n", 1);
	else if (state == 2)
		ft_putstr_fd(" \x1B[33mis sleeping\x1B[0m\n", 1);
	else if (state == 3)
		ft_putstr_fd(" \x1B[34mis thinking\x1B[0m\n", 1);
	else
		ft_putstr_fd(" \x1B[35mhas taken a fork\x1B[0m\n", 1);
	sem_post(philo->logger);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	int		err;
	int		err_t;

	philo = (t_philo *)malloc(sizeof(t_philo));
	philo->time = get_timestamp();
	err = arg_check(argc, argv, philo);
	if (err)
		return (1);
	err_t = create_threads(philo, get_timestamp());
	if (err_t)
		return (1);
}
