/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:48:47 by fli               #+#    #+#             */
/*   Updated: 2024/07/29 22:50:57 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	use_brain(t_arg *args, t_philo *philos, int index)
{
	pthread_mutex_lock(&args->talking_stick);
	printf("%ld %d is thinking\n", time_from_start(args), philos[index].name);
	pthread_mutex_unlock(&args->talking_stick);
}

static void	seize_fork(t_fork *fork, t_arg *args, t_philo *philos, int i)
{
	pthread_mutex_lock(&fork->fork_mutex);
	pthread_mutex_lock(&args->talking_stick);
	printf("%ld %d has taken a fork\n", time_from_start(args), philos[i].name);
	pthread_mutex_unlock(&args->talking_stick);
}

static void	take_forks(t_arg *args, t_philo *philos, int index)
{
	t_fork			*left_fork;
	t_fork			*right_fork;

	left_fork = &(args->forks)[philos[index].left_fork];
	right_fork = &(args->forks)[philos[index].right_fork];
	check_alive(args, philos, index);
	if ((index + 1) % 2 == 0)
	{
		seize_fork(right_fork, args, philos, index);
		check_alive(args, philos, index);
		seize_fork(left_fork, args, philos, index);
		check_alive(args, philos, index);
	}
	else
	{
		seize_fork(left_fork, args, philos, index);
		check_alive(args, philos, index);
		seize_fork(right_fork, args, philos, index);
		check_alive(args, philos, index);
	}
}

void	eat_spaghet(t_arg *args, t_philo *philos, int index)
{
	t_fork			*left_fork;
	t_fork			*right_fork;

	left_fork = &(args->forks)[philos[index].left_fork];
	right_fork = &(args->forks)[philos[index].right_fork];
	take_forks(args, philos, index);
	pthread_mutex_lock(&args->talking_stick);
	printf("%ld %d is eating\n", time_from_start(args), philos[index].name);
	pthread_mutex_unlock(&args->talking_stick);
	usleep(((args->eat_t) * 1000));
	pthread_mutex_unlock(&left_fork->fork_mutex);
	pthread_mutex_unlock(&right_fork->fork_mutex);
	pthread_mutex_lock(&philos[index].n_meal_mutex);
	philos[index].n_meal = (philos[index].n_meal) + 1;
	pthread_mutex_unlock(&philos[index].n_meal_mutex);
	pthread_mutex_lock(&philos[index].last_meal_mutex);
	philos[index].last_meal = get_time_ms();
	pthread_mutex_unlock(&philos[index].last_meal_mutex);
}

void	take_nap(t_arg *args, t_philo *philos, int index)
{
	pthread_mutex_lock(&args->talking_stick);
	printf("%ld %d is sleeping\n", time_from_start(args), philos[index].name);
	pthread_mutex_unlock(&args->talking_stick);
	usleep((args->sleep_t) * 1000);
	check_alive(args, philos, index);
}
