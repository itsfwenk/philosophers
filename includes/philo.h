/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:17:52 by fli               #+#    #+#             */
/*   Updated: 2024/07/26 16:26:31 by fli              ###   ########.fr       */
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

#  define TRUE 1
#  define FALSE 0

typedef struct s_fork
{
	pthread_mutex_t	fork_mutex;
	int				belong_to;
}	t_fork;

typedef struct s_philo
{
	int			name;
	int			left_fork;
	int			right_fork;
	int			n_meal;
	int			exist;
	time_t		last_meal;
	pthread_t	tid;
}	t_philo;

typedef struct s_arg
{
	int		n_philo;
	int		die_t;
	int		eat_t;
	int		sleep_t;
	int		min_meals;
	int		current;
	time_t	start_time;
	t_fork	*forks;
	t_philo	*philos;
} t_arg;

/////////////////////// PHILO ///////////////////////


/////////////////////// PHILO_UTILS ///////////////////////

int			ft_atoi(char *s);

void		get_args(int ac, char **av, t_arg *args);

suseconds_t	get_time_ms(void);

time_t		time_from_start(t_arg *args);

/////////////////////// PHILO_UTILS2 ///////////////////////

int			check_alive(t_arg *args, t_philo *philos, int name);

int			count_philo(t_arg *args);

int			check_meals(t_arg *args, t_philo *philos);

void		join_philo(t_philo * philos);

void	philo_id(t_arg *args); ////

void	print_args(t_arg *args);/////

/////////////////////// ROUTINE ///////////////////////

void		*philo_routine(void *args);

void		start_philo(t_arg *args);

/////////////////////// CLEAN ///////////////////////

void		dish_washer(t_arg *args);

void		detach_philo(t_arg *args);

#endif
