/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:48:47 by fli               #+#    #+#             */
/*   Updated: 2024/07/25 15:07:58 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_fork(t_arg *args, t_philo **philos, int name)
{
	t_fork			*left_fork;
	t_fork			*right_fork;
	struct timeval	tp;

	left_fork = (args->forks)[philos[name]->left_fork];
	right_fork = (args->forks)[philos[name]->right_fork];
	check_alive(args, philos, name);
	pthread_mutex_lock(&left_fork->fork_mutex);
	printf("%ld %d has taken a fork\n", time_from_start(args), name);
	check_alive(args, philos, name);
	pthread_mutex_lock(&right_fork->fork_mutex);
	printf("%ld %d has taken a fork\n", time_from_start(args), name);
	printf("%ld %d is eating\n", time_from_start(args), name);
	philos[name]->n_meal = (philos[name]->n_meal) + 1;
	usleep((args->eat_t) * 1000);
	check_alive(args, philos, name);
	gettimeofday(&tp, NULL);
	philos[name]->last_meal = tp.tv_sec;
	pthread_mutex_unlock(&left_fork->fork_mutex);
	pthread_mutex_unlock(&right_fork->fork_mutex);
}

static void	take_nap(t_arg *args, t_philo **philos, int name)
{
	printf("%ld %d is sleeping\n", time_from_start(args), name);
	usleep((args->sleep_t) * 1000);
	check_alive(args, philos, name);
	printf("%ld %d is thinking\n", time_from_start(args), name);
}

void	*philo_routine(void *args)
{

	while (check_meals(args, ((t_arg *)args)->philos) == FALSE)
	{
		take_fork(((t_arg *)args), ((t_arg *)args)->philos, ((t_arg *)args)->current);
		take_nap(((t_arg *)args), ((t_arg *)args)->philos, ((t_arg *)args)->current);
	}
	return (NULL);
}

void	start_philo(t_arg *args)
{
	pthread_t	current_tid;

	current_tid = args->philos[args->current]->tid;
	pthread_create(&current_tid, NULL, philo_routine, args);
	pthread_join(current_tid, NULL);
}
