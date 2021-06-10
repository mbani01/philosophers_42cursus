/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani <mbani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 14:43:13 by mbani             #+#    #+#             */
/*   Updated: 2021/06/09 18:27:24 by mbani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>
# include <sys/wait.h>
# include <signal.h>

typedef struct s_philo{
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			time;
	int				nbr_of_philo;
	int				nbr_of_time_each_philo_must_eat;
	int				alive;
	pthread_t		super;
	pid_t			*pid;
	sem_t			*forks;
	sem_t			*logger;
	sem_t			*death;
}				t_philo;
typedef struct s_args{
	long			creation;
	int				count;
	int				grabing;
	int				iseating;
	int				eaten;
	t_philo			*philo;
}				t_args;
long	ft_atoi(const char *str);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(long n, int fd);
int		error_argument(void);
int		init_args(char **argv, t_philo *philo);
int		arg_check(int argc, char **argv, t_philo *philo);
int		create_threads(t_philo *philo, long start);
long	get_timestamp(void);
t_args	**init_thread_args(t_philo *philo);
void	*philoshopers(t_args *philo);
void	grab_forks(t_args *philo);
void	eat(t_args *philo);
void	release_forks(t_args *philo);
void	ph_sleep(t_args *philo);
int		create_threads(t_philo *philo, long start);
void	ft_logger(int state, long time, int id, t_philo *philo);
void	*supervisors(void *arg);
void	init_semaphores(t_philo *philo);
#endif