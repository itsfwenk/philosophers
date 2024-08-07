/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:17:52 by fli               #+#    #+#             */
/*   Updated: 2024/08/06 15:20:33 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

# define TRUE 1
# define FALSE 0

typedef struct s_fork
{
	pthread_mutex_t	fork_mutex;
	int				belong_to;
}	t_fork;

typedef struct s_philo
{
	int				name;
	int				left_fork;
	int				right_fork;
	pthread_mutex_t	n_meal_mutex;
	int				n_meal;
	int				exist;
	pthread_mutex_t	last_meal_mutex;
	time_t			last_meal;
	pthread_t		tid;
}	t_philo;

typedef struct s_arg
{
	int				n_philo;
	int				die_t;
	int				eat_t;
	int				sleep_t;
	int				min_meals;
	pthread_mutex_t	current_mutex;
	int				current;
	pthread_mutex_t	armageddon_mutex;
	int				armageddon;
	pthread_mutex_t	talking_stick;
	time_t			start_time;
	t_fork			*forks;
	t_philo			*philos;
}	t_arg;

/////////////////////// CHECK_ARG ///////////////////////

int			check_arg(int ac, char **av);

/////////////////////// CLEAN ///////////////////////

void		destroy_mutexes(t_arg *args, t_fork	*forks, t_philo *philos);

void		until_end(t_arg *args, t_philo *philos);

void		join_philo(t_arg *args, t_philo *philos);

/////////////////////// MOTHER ///////////////////////

void		create_philo(t_arg *args, t_philo *philos);

/////////////////////// PHILO_UTILS ///////////////////////

int			ft_atoi(char *s);

void		get_args(int ac, char **av, t_arg *args);

suseconds_t	get_time_ms(void);

time_t		time_from_start(t_arg *args);

void		print_action(t_arg *args, int name, char *action);

/////////////////////// PHILO_UTILS2 ///////////////////////

int			check_alive(t_arg *args, t_philo *philos, int name);

int			check_meals(t_arg *args, t_philo *philos);

int			take_nap(t_arg *args, t_philo *philos, int index);

/////////////////////// ROUTINE_UTILS ///////////////////////

int			seize_fork(t_fork *fork, t_arg *args, t_philo *philos, int i);

int			eat_spaghet(t_arg *args, t_philo *philos, int index);

/////////////////////// ROUTINE ///////////////////////

void		do_something(suseconds_t start, int waiting_time);

void		*philo_routine(void *args);

void		start_philo(t_arg *args);

#endif
