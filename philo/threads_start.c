/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_start.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani <mbani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 15:37:55 by mbani             #+#    #+#             */
/*   Updated: 2021/06/10 09:44:45 by mbani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*philoshopers(void *arg)
{
	t_args		*philo;

	philo = ((t_args *)arg);
	philo->l_fork = philo->count - 1;
	philo->r_fork = (philo->count) % philo->philo->nbr_of_philo;
	while (1)
	{
		grab_forks(philo);
		eat(philo);
		release_forks(philo);
		ph_sleep(philo);
		ft_logger(3, get_timestamp(), philo->count, philo->philo);
	}
	return (NULL);
}

void	grab_forks(t_args *philo)
{
	pthread_mutex_lock(&philo->philo->forks[philo->r_fork]);
	ft_logger(4, get_timestamp(), philo->count, philo->philo);
	pthread_mutex_lock(&philo->philo->forks[philo->l_fork]);
	ft_logger(4, get_timestamp(), philo->count, philo->philo);
}

void	eat(t_args *philo)
{
	long	start;

	philo->creation = get_timestamp();
	philo->iseating = 1;
	pthread_mutex_lock(&philo->death);
	philo->philo->eaten[philo->count - 1] += 1;
	ft_logger(1, get_timestamp(), philo->count, philo->philo);
	start = get_timestamp();
	usleep(philo->philo->time_to_eat * 1000.0 - 20000);
	while (get_timestamp() - start < philo->philo->time_to_eat)
		continue ;
	pthread_mutex_unlock(&philo->death);
	philo->iseating = 0;
}

void	release_forks(t_args *philo)
{
	pthread_mutex_unlock(&philo->philo->forks[philo->l_fork]);
	pthread_mutex_unlock(&philo->philo->forks[philo->r_fork]);
}

void	ph_sleep(t_args *philo)
{
	long	start;

	ft_logger(2, get_timestamp(), philo->count, philo->philo);
	start = get_timestamp();
	usleep(philo->philo->time_to_sleep * 1000.0 - 20000);
	while (get_timestamp() - start < philo->philo->time_to_sleep)
		continue ;
}
