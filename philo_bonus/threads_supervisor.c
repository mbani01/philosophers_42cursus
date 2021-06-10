/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_supervisor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani <mbani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 15:50:07 by mbani             #+#    #+#             */
/*   Updated: 2021/06/09 18:59:23 by mbani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	death(t_args *philo, long time)
{
	if (time >= philo->philo->time_to_die)
	{
		sem_wait(philo->philo->logger);
		ft_putnbr_fd(get_timestamp() - philo->philo->time, 1);
		ft_putstr_fd(" ", 1);
		ft_putnbr_fd(philo->count, 1);
		ft_putstr_fd(" \x1B[31mdied\x1B[0m\n", 1);
		exit (0);
	}
}

void	free_allocated_mem(t_args *philo)
{
	int	i;
	int	nbr;

	nbr = philo->philo->nbr_of_philo;
	i = 0;
	free(philo);
}

void	eaten(t_args *philo)
{
	if (philo->philo->nbr_of_time_each_philo_must_eat != -1 && \
	philo->eaten == philo->philo->nbr_of_time_each_philo_must_eat)
	{
		while (philo->grabing)
		{
			sem_post(philo->philo->forks);
			philo->grabing--;
		}
		usleep(1000);
		free_allocated_mem(philo);
		exit(1);
	}
}

void	*supervisors(void *arg)
{
	long	time;
	t_args	*philo;

	philo = (t_args *)arg;
	while (1)
	{
		if (philo->iseating != 1)
		{	
			time = get_timestamp() - philo->creation;
			sem_wait(philo->philo->death);
			death(philo, time);
			sem_post(philo->philo->death);
		}
		eaten(arg);
		usleep(5000);
	}
}
