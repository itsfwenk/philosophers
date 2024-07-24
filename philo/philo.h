/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:17:52 by fli               #+#    #+#             */
/*   Updated: 2024/07/24 16:31:03 by fli              ###   ########.fr       */
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
#  define AVAILABLE 2
#  define UNAVAILABLE 3

typedef struct s_fork
{
	pthread_mutex_t	fork_mutex;
	int				belong_to;
}	t_fork;

typedef struct s_arg
{
	int			n_philo;
	int			die_t;
	int			eat_t;
	int			sleep_t;
	time_t	start_time;
	t_fork		**forks;
} t_arg;

typedef struct s_philo
{
	int			name;
	int			left_fork;
	int			right_fork;
	pthread_t	tid;
}	t_philo;


/////////////////////// PHILO ///////////////////////


/////////////////////// PHILO_UTILS ///////////////////////

int		ft_atoi(char *s);

void	get_args(char **av, t_arg *args);

time_t	time_from_start(t_arg *args);

#endif
