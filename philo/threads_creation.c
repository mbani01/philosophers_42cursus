/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_creation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani <mbani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 15:35:30 by mbani             #+#    #+#             */
/*   Updated: 2021/06/10 09:44:10 by mbani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	create_odd_philo(t_args **tmp_philo, t_philo *philo, long start)
{
	int	i;
	int	error;

	i = 0;
	while (i < philo->nbr_of_philo)
	{
		tmp_philo[i] = malloc(sizeof(t_args));
		tmp_philo[i]->philo = philo;
		tmp_philo[i]->count = i + 1;
		tmp_philo[i]->creation = start;
		tmp_philo[i]->iseating = 0;
		pthread_mutex_init(&tmp_philo[i]->death, NULL);
		error = pthread_create(&philo->philo_threads[i], NULL, \
		philoshopers, (void *) tmp_philo[i]);
		if (error != 0)
		{
			printf("thread cannot be created !\n");
			return (-1);
		}
		i += 2;
	}
	return (0);
}

int	create_even_philo(t_args **tmp_philo, t_philo *philo, long start)
{
	int	i;
	int	error;

	i = 1;
	while (i < philo->nbr_of_philo)
	{
		tmp_philo[i] = malloc(sizeof(t_args));
		tmp_philo[i]->philo = philo;
		tmp_philo[i]->count = i + 1;
		tmp_philo[i]->creation = start;
		pthread_mutex_init(&tmp_philo[i]->death, NULL);
		error = pthread_create(&philo->philo_threads[i], NULL, \
		philoshopers, (void *) tmp_philo[i]);
		if (error != 0)
		{
			printf("thread cannot be created !\n");
			return (-1);
		}
		i += 2;
	}
	return (0);
}

int	create_threads(t_philo *philo, long start)
{
	int		error;
	t_args	**tmp_philo;

	tmp_philo = init_thread_args(philo);
	if (!tmp_philo)
		return (-1);
	error = create_odd_philo(tmp_philo, philo, start);
	if (error)
		return (1);
	usleep(1000);
	error = create_even_philo(tmp_philo, philo, start);
	if (error)
		return (1);
	return (supervisors(tmp_philo, philo));
}
