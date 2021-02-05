/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:34:51 by user42            #+#    #+#             */
/*   Updated: 2021/02/05 18:05:15 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>

# define MIN_EAT 0

# define SUCCESS 0
# define FAILED -1

# define ERR_MALLOC 1
# define ERR_NUM_ARG 2
# define ERR_NUM_PHILO 3
# define ERR_TIME 4
# define ERR_INIT 5
# define ERR_INIT_MUTEX 6

# define MSG_FORK 0
# define MSG_EAT 1
# define MSG_SLEEP 2
# define MSG_THINK 3
# define MSG_DIED 4
# define MSG_ENDED 5

# define SEM_LOCK "sem_lock"
# define SEM_FORK "sem_fork"
# define SEM_DEAD "sem_dead"
# define SEM_MEAL "sem_meal"
# define SEM_MSGS "sem_msgs"

typedef struct	s_data
{
	int				status;
	int				nb_meal;
	int				id;
	struct timeval	last_meal;
	pthread_t		monitor;
	pid_t			pid;
}				t_data;

typedef struct	s_philo
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_must_eat;
	int 			status;
	sem_t			*forks;
	sem_t			*lock;
	sem_t			*meals;
	sem_t			*corpse;
	sem_t			*print;
	t_data			**philo;
}				t_philo;

extern t_philo	*g_philo;

int				get_param(char **av);

int				clean_exit(int status);

void			*watch_dead(void *arg);
void			*watch_meal(void *arg);
void			report_corpse(int i);
void			report_meal(int i);
void			launch_thread(void);

t_data			*data_philo(int i);
void			*philo_monitor(void *arg);
void			philo_fork(t_data *philo);
void			philo_eat(t_data *philo);
void			philo_rest(t_data *philo);

void			print_msg(int id, int msg);

char			*ft_strcat(char *dest, char *srcs);
int				get_timestamp(struct timeval *time);
int				is_whitespace(char c);
int				ft_atoi(const char *s);
char			*ft_itoa_dec(int num);

#endif
