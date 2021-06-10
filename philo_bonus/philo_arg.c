/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani <mbani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 15:28:01 by mbani             #+#    #+#             */
/*   Updated: 2021/06/09 18:27:15 by mbani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int	error_argument(void)
{
	printf("Error arguments!\n");
	return (-1);
}

int	init_args(char **argv, t_philo *philo)
{
	philo->nbr_of_philo = (int) ft_atoi(argv[1]);
	if (philo->nbr_of_philo == 0 || philo->nbr_of_philo == -1)
		return (error_argument());
	philo->time_to_die = ft_atoi(argv[2]);
	if (philo->time_to_die == 0 || philo->time_to_die == -1)
		return (error_argument());
	philo->time_to_eat = ft_atoi(argv[3]);
	if (philo->time_to_eat == 0 || philo->time_to_eat == -1)
		return (error_argument());
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (philo->time_to_sleep == 0 || philo->time_to_sleep == -1)
		return (error_argument());
	if (argv[5])
	{
		philo->nbr_of_time_each_philo_must_eat = (int) ft_atoi(argv[5]);
		if (philo->nbr_of_time_each_philo_must_eat == 0 || \
		philo->nbr_of_time_each_philo_must_eat == -1)
			return (error_argument());
	}
	else
		philo->nbr_of_time_each_philo_must_eat = -1;
	return (0);
}

int	arg_check(int argc, char **argv, t_philo *philo)
{
	if (argc != 5 && argc != 6)
		return (error_argument());
	else
		return (init_args(argv, philo));
}

long	get_timestamp(void)
{
	struct timeval	creation;
	long			timestamp;

	gettimeofday(&creation, NULL);
	timestamp = (creation.tv_sec * 1000.0 + creation.tv_usec / 1000.0);
	return (timestamp);
}

t_args	**init_thread_args(t_philo *philo)
{
	t_args	**tmp_philo;
	int		i;

	i = philo->nbr_of_philo;
	tmp_philo = (t_args **)malloc(sizeof(t_args *) * philo->nbr_of_philo);
	philo->pid = (pid_t *) malloc(sizeof(pid_t) * \
	philo->nbr_of_philo);
	init_semaphores(philo);
	while (--i >= 0)
	{
		if (!tmp_philo || \
		!philo->forks || philo->death == SEM_FAILED)
		{
			printf("fatal error !\n");
			return (NULL);
		}
	}
	return (tmp_philo);
}
