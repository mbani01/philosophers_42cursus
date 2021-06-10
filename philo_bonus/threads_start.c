/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_start.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani <mbani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 15:37:55 by mbani             #+#    #+#             */
/*   Updated: 2021/06/09 18:38:53 by mbani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*philoshopers(t_args *philo)
{
	t_args	*tmp;
	int		error;

	if (philo->count % 2 == 0)
		usleep(1000);
	tmp = malloc(sizeof(t_args *));
	philo->philo->alive = 1;
	philo->iseating = 0;
	tmp = philo;
	error = pthread_create(&philo->philo->super, NULL, \
	supervisors, (void *)tmp);
	if (error)
	{
		printf("fatal error!\n");
		exit(1);
	}
	while (1 && philo->philo->alive)
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
	sem_wait(philo->philo->forks);
	philo->grabing++;
	ft_logger(4, get_timestamp(), philo->count, philo->philo);
	sem_wait(philo->philo->forks);
	philo->grabing++;
	ft_logger(4, get_timestamp(), philo->count, philo->philo);
}

void	eat(t_args *philo)
{
	long	start;

	philo->creation = get_timestamp();
	sem_wait(philo->philo->death);
	philo->iseating = 1;
	philo->eaten += 1;
	ft_logger(1, get_timestamp(), philo->count, philo->philo);
	start = get_timestamp();
	usleep(philo->philo->time_to_eat * 1000.0 - 20000);
	while (get_timestamp() - start < philo->philo->time_to_eat)
		continue ;
	sem_post(philo->philo->death);
	philo->iseating = 0;
}

void	release_forks(t_args *philo)
{
	sem_post(philo->philo->forks);
	sem_post(philo->philo->forks);
	philo->grabing = 0;
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
