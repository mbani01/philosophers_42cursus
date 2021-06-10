/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani <mbani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 14:43:13 by mbani             #+#    #+#             */
/*   Updated: 2021/06/10 09:51:53 by mbani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo{
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			time;
	int				*eaten;
	int				nbr_of_philo;
	int				nbr_of_time_each_philo_must_eat;
	pthread_t		*philo_threads;
	pthread_mutex_t	*forks;
	pthread_mutex_t	logger;
}				t_philo;
typedef struct s_args{
	long			creation;
	int				count;
	int				l_fork;
	int				r_fork;
	t_philo			*philo;
	int				iseating;
	pthread_mutex_t	death;
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
void	*philoshopers(void *arg);
void	grab_forks(t_args *philo);
void	eat(t_args *philo);
void	release_forks(t_args *philo);
void	ph_sleep(t_args *philo);
int		create_threads(t_philo *philo, long start);
void	ft_logger(int state, long time, int id, t_philo *philo);
int		supervisors(t_args **philo, t_philo *arg);
#endif