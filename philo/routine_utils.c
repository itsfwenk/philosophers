/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:48:47 by fli               #+#    #+#             */
/*   Updated: 2024/07/30 20:24:32 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	use_brain(t_arg *args, t_philo *philos, int index)
{
	pthread_mutex_lock(&args->talking_stick);
	printf("%ld %d is thinking\n", time_from_start(args), philos[index].name);
	pthread_mutex_unlock(&args->talking_stick);
}

static int	seize_fork(t_fork *fork, t_arg *args, t_philo *philos, int i)
{
	pthread_mutex_lock(&fork->fork_mutex);
	pthread_mutex_lock(&args->talking_stick);
	printf("%ld %d has taken a fork %d\n", time_from_start(args), philos[i].name, fork->belong_to);
	pthread_mutex_unlock(&args->talking_stick);
	if (check_alive(args, philos, i) == FALSE)
		return (FALSE);
	return (TRUE);
}

static int	take_forks(t_arg *args, t_philo *philos, int index)
{
	t_fork			*left_fork;
	t_fork			*right_fork;

	left_fork = &(args->forks)[philos[index].left_fork];
	right_fork = &(args->forks)[philos[index].right_fork];
	if (check_alive(args, philos, index) == FALSE)
		return (FALSE);
	if ((index) % 2 == 0)
	{
		if (seize_fork(right_fork, args, philos, index) == FALSE)
			return (FALSE);
		if (seize_fork(left_fork, args, philos, index) == FALSE)
			return (FALSE);
	}
	else
	{
		if (seize_fork(left_fork, args, philos, index) == FALSE)
			return (FALSE);
		if (seize_fork(right_fork, args, philos, index) == FALSE)
			return (FALSE);
	}
	return (TRUE);
}

int	eat_spaghet(t_arg *args, t_philo *philos, int index)
{
	t_fork			*left_fork;
	t_fork			*right_fork;

	left_fork = &(args->forks)[philos[index].left_fork];
	right_fork = &(args->forks)[philos[index].right_fork];
	if (take_forks(args, philos, index) == FALSE)
		return (FALSE);
	pthread_mutex_lock(&args->talking_stick);
	printf("%ld %d is eating\n", time_from_start(args), philos[index].name);
	pthread_mutex_unlock(&args->talking_stick);
	do_something(args->eat_t);
	pthread_mutex_unlock(&left_fork->fork_mutex);
	pthread_mutex_unlock(&right_fork->fork_mutex);
	pthread_mutex_lock(&philos[index].n_meal_mutex);
	philos[index].n_meal = (philos[index].n_meal) + 1;
	pthread_mutex_unlock(&philos[index].n_meal_mutex);
	pthread_mutex_lock(&philos[index].last_meal_mutex);
	philos[index].last_meal = get_time_ms();
	pthread_mutex_unlock(&philos[index].last_meal_mutex);
	return (TRUE);
}

int	take_nap(t_arg *args, t_philo *philos, int index)
{
	pthread_mutex_lock(&args->talking_stick);
	printf("%ld %d is sleeping\n", time_from_start(args), philos[index].name);
	pthread_mutex_unlock(&args->talking_stick);
	do_something(args->sleep_t);
	if (check_alive(args, philos, index) == FALSE)
		return (FALSE);
	return (TRUE);
}
