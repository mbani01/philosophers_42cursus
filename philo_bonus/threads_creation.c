/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_creation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani <mbani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 15:35:30 by mbani             #+#    #+#             */
/*   Updated: 2021/06/10 11:04:33 by mbani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	create_odd_philo(t_args **tmp_philo, t_philo *philo, long start)
{
	int	i;

	i = 0;
	while (i < philo->nbr_of_philo)
	{
		tmp_philo[i] = malloc(sizeof(t_args));
		tmp_philo[i]->philo = philo;
		tmp_philo[i]->count = i + 1;
		tmp_philo[i]->creation = start;
		tmp_philo[i]->eaten = 0;
		tmp_philo[i]->grabing = 0;
		philo->pid[i] = fork();
		if (philo->pid[i] < 0)
		{
			printf("fatal error !\n");
			exit(1);
		}
		else if (philo->pid[i] == 0)
			philoshopers(tmp_philo[i]);
		else
			i += 2;
	}
}

void	create_even_philo(t_args **tmp_philo, t_philo *philo, long start)
{
	int	i;

	i = 1;
	while (i < philo->nbr_of_philo)
	{
		tmp_philo[i] = malloc(sizeof(t_args));
		tmp_philo[i]->philo = philo;
		tmp_philo[i]->count = i + 1;
		tmp_philo[i]->creation = start;
		tmp_philo[i]->eaten = 0;
		tmp_philo[i]->grabing = 0;
		philo->pid[i] = fork();
		if (philo->pid[i] < 0)
		{
			printf("fatal error !\n");
			exit(1);
		}
		else if (philo->pid[i] == 0)
			philoshopers(tmp_philo[i]);
		else
			i += 2;
	}
}

void	init_and_launch(t_args **tmp_philo, long start, t_philo *philo)
{
	tmp_philo = init_thread_args(philo);
	if (!tmp_philo || philo->forks == SEM_FAILED)
		exit (1);
	create_odd_philo(tmp_philo, philo, start);
	usleep(1000);
	create_even_philo(tmp_philo, philo, start);
}

int	create_threads(t_philo *philo, long start)
{
	int		i;
	int		status;
	t_args	**tmp_philo;
	t_philo	*tmp;

	tmp_philo = NULL;
	tmp = philo;
	init_and_launch(tmp_philo, start, philo);
	i = 0;
	while (i < philo->nbr_of_philo)
	{
		waitpid((pid_t) - 1, & status, 0);
		status = WEXITSTATUS(status);
		if (status == 0)
			break ;
		i++;
	}
	if (status == 1)
		printf("each philo has eaten %d times\n", \
		philo->nbr_of_time_each_philo_must_eat);
	i = -1;
	while (++i < philo->nbr_of_philo)
		kill(philo->pid[i], SIGKILL);
	free(tmp);
	exit (0);
}

void	init_semaphores(t_philo *philo)
{
	sem_unlink("/sem_logger");
	philo->logger = sem_open("/sem_logger", O_CREAT | O_EXCL, 644, 1);
	sem_unlink("/sem_forks");
	philo->forks = sem_open("/sem_forks", O_CREAT | O_EXCL, 644, \
	philo->nbr_of_philo);
	sem_unlink("/sem_death");
	philo->death = sem_open("/sem_death", O_CREAT | O_EXCL, 644, \
	philo->nbr_of_philo);
}
