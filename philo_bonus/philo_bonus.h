/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:17:52 by fli               #+#    #+#             */
/*   Updated: 2024/08/01 20:30:11 by fli              ###   ########.fr       */
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
# include <semaphore.h>

# define TRUE 1
# define FALSE 0

typedef struct s_philo
{
	int			name;
	// int			n_meal;
	time_t		last_meal;
	pid_t		pid;
	int			status;
	pthread_t	tid;
	pthread_t	check_meal_tid;
	sem_t		eating_sem;
}	t_philo;

typedef struct s_arg
{
	int			n_philo;
	int			die_t;
	int			eat_t;
	int			sleep_t;
	int			min_meals;
	int			current;
	sem_t		*meals_sem;
	int			*meals;
	pthread_t	all_eat;
	time_t		start_time;
	t_philo		*philos;
	sem_t		*armageddon;
	int			stop_dinner;
	sem_t		*talking_stick;
	sem_t		*forks;
}	t_arg;

/////////////////////// CLEAN ///////////////////////

void		until_end(t_arg *args, t_philo *philos);

void		join_philo(t_arg *args, t_philo *philos);

/////////////////////// MOTHER ///////////////////////

void		wait_philos(t_arg *args);

int			create_philo(t_arg *args, t_philo *philos);

/////////////////////// PHILO ///////////////////////


/////////////////////// PHILO_UTILS ///////////////////////

int			ft_atoi(char *s);

void		get_args(int ac, char **av, t_arg *args);

time_t		get_time_ms(void);

time_t		time_from_start(t_arg *args);

void		print_action(t_arg *args, int name, char *action);

/////////////////////// PHILO_UTILS2 ///////////////////////

int			check_alive(t_arg *args, t_philo *philos, int name);

int			check_meals(t_arg *args, t_philo *philos);

int			optimal_frequency(t_arg *args);

void	philo_id(t_arg *args); ////

void	print_args(t_arg *args);/////

void	show_all_philo(t_arg *args);///

/////////////////////// ROUTINE_UTILS ///////////////////////

int			eat_spaghet(t_arg *args, t_philo *philos, int index);

int			take_nap(t_arg *args, t_philo *philos, int index);

/////////////////////// ROUTINE ///////////////////////

void		do_something(int waiting_time);

int			check_stop(t_arg *args);

void		philo_routine(t_arg *args, t_philo *philos, int index);

void		start_philo(t_arg *args, t_philo *philos, int index);

#endif
