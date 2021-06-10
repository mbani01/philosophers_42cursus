/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_supervisor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani <mbani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 15:50:07 by mbani             #+#    #+#             */
/*   Updated: 2021/06/10 10:12:19 by mbani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	death(t_args *philo, long time)
{
	if (time >= philo->philo->time_to_die)
	{
		pthread_mutex_lock(&philo->philo->logger);
		ft_putnbr_fd(get_timestamp() - philo->philo->time, 1);
		ft_putstr_fd(" ", 1);
		ft_putnbr_fd(philo->count, 1);
		ft_putstr_fd(" \x1B[31mdied\x1B[0m\n", 1);
		return (1);
	}
	return (0);
}

int	eaten(t_philo *philo)
{
	int	i;

	i = 0;
	if (philo->nbr_of_time_each_philo_must_eat == -1)
		return (0);
	while (philo->eaten[i] && philo->eaten[i] >= \
	philo->nbr_of_time_each_philo_must_eat)
		i++;
	if (i >= philo->nbr_of_philo)
	{
		usleep(1000);
		pthread_mutex_lock(&philo->logger);
		ft_putstr_fd("each philo has eaten at least ", 1);
		ft_putnbr_fd(philo->nbr_of_time_each_philo_must_eat, 1);
		ft_putstr_fd(" times\n", 1);
		return (1);
	}
	return (0);
}

void	free_allocated_mem(t_args **philo)
{
	int	i;
	int	nbr;

	nbr = philo[0]->philo->nbr_of_philo;
	i = 0;
	if (philo[0]->philo)
	{
		free(philo[0]->philo->forks);
		free(philo[0]->philo->philo_threads);
		free(philo[0]->philo->eaten);
	}
	while (i < nbr)
	{
		free(philo[i]);
		i++;
	}
	free(philo);
}

int	check_death(t_args *philo)
{
	long	time;

	if (!philo->iseating)
	{	
		time = get_timestamp() - philo->creation;
		pthread_mutex_lock(&philo->death);
		if (death(philo, time))
			return (1);
		pthread_mutex_unlock(&philo->death);
	}
	usleep(800);
	return (0);
}

int	supervisors(t_args **philo, t_philo *arg)
{
	int		i;
	int		ret;

	while (1)
	{
		i = philo[0]->philo->nbr_of_philo;
		while (--i >= 0)
		{
			ret = check_death(philo[i]);
			if (ret)
			{
				free_allocated_mem(philo);
				return (0);
			}
		}
		if (eaten(arg))
		{
			free_allocated_mem(philo);
			return (0);
		}
	}
}
