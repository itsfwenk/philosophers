/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:17:52 by fli               #+#    #+#             */
/*   Updated: 2024/08/02 18:10:22 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include <semaphore.h>
# include <sys/types.h>
# include <sys/wait.h>

# define TRUE 1
# define FALSE 0

typedef struct s_philo
{
	int			name;
	int			n_meal;
	time_t		last_meal;
	pid_t		pid;
	pthread_t	tid;
}	t_philo;

typedef struct s_arg
{
	int			n_philo;
	int			die_t;
	int			eat_t;
	int			sleep_t;
	int			min_meals;
	int			current;
	int			stop_dinner;
	time_t		start_time;
	pthread_t	dessert_thread;
	t_philo		*philos;
	sem_t		*dessert;
	sem_t		*armageddon;
	sem_t		*talking_stick;
	sem_t		*forks;
}	t_arg;

/////////////////////// DESSERT///////////////////////

void		*check_dessert(void *args);

void		launch_dessert(t_arg *args);

/////////////////////// MOTHER ///////////////////////

void		destroy_sem(t_arg *args);

void		wait_philos(t_arg *args);

int			create_philo(t_arg *args, t_philo *philos);

/////////////////////// PHILO_UTILS ///////////////////////

int			ft_atoi(char *s);

void		get_args(int ac, char **av, t_arg *args);

time_t		get_time_ms(void);

time_t		time_from_start(t_arg *args);

void		print_action(t_arg *args, int name, char *action);

/////////////////////// PHILO_UTILS2 ///////////////////////

int			optimal_frequency(t_arg *args);

int			check_arg(int ac, char **av);

/////////////////////// ROUTINE_UTILS ///////////////////////

void		do_something(time_t start, int waiting_time);

void		eat_spaghet(t_arg *args, t_philo *philos, int index);

void		take_nap(t_arg *args, t_philo *philos, int index);

/////////////////////// ROUTINE ///////////////////////

int			check_stop(t_arg *args);

void		*check_death(void *args);

void		philo_routine(t_arg *args, t_philo *philos, int index);

void		start_philo(t_arg *args, t_philo *philos, int index);

#endif
