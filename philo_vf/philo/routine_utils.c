/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:48:47 by fli               #+#    #+#             */
/*   Updated: 2024/08/02 17:40:44 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	seize_fork(t_fork *fork, t_arg *args, t_philo *philos, int i)
{
	pthread_mutex_lock(&fork->fork_mutex);
	print_action(args, philos[i].name, "has taken a fork");
	return (TRUE);
}

static int	take_forks(t_arg *args, t_philo *philos, int index)
{
	t_fork			*left_fork;
	t_fork			*right_fork;

	left_fork = &(args->forks)[philos[index].left_fork];
	right_fork = &(args->forks)[philos[index].right_fork];
	if ((index + 1) % 2 == 0)
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

static void	if_armageddon(t_arg *args, t_philo *philos, int index)
{
	t_fork			*left_fork;
	t_fork			*right_fork;

	left_fork = &(args->forks)[philos[index].left_fork];
	right_fork = &(args->forks)[philos[index].right_fork];
	pthread_mutex_unlock(&args->armageddon_mutex);
	pthread_mutex_unlock(&philos[index].last_meal_mutex);
	pthread_mutex_unlock(&left_fork->fork_mutex);
	pthread_mutex_unlock(&right_fork->fork_mutex);
}

static void	update_meal_info(t_philo *philos, int index)
{
	pthread_mutex_lock(&philos[index].n_meal_mutex);
	philos[index].n_meal = (philos[index].n_meal) + 1;
	pthread_mutex_unlock(&philos[index].n_meal_mutex);
}

int	eat_spaghet(t_arg *args, t_philo *philos, int index)
{
	t_fork			*left_fork;
	t_fork			*right_fork;
	suseconds_t		start_time;

	left_fork = &(args->forks)[philos[index].left_fork];
	right_fork = &(args->forks)[philos[index].right_fork];
	if (take_forks(args, philos, index) == FALSE)
		return (FALSE);
	start_time = get_time_ms();
	print_action(args, philos[index].name, "is eating");
	pthread_mutex_lock(&args->armageddon_mutex);
	pthread_mutex_lock(&philos[index].last_meal_mutex);
	if (args->armageddon == TRUE)
	{
		if_armageddon(args, philos, index);
		return (FALSE);
	}
	philos[index].last_meal = get_time_ms();
	pthread_mutex_unlock(&args->armageddon_mutex);
	pthread_mutex_unlock(&philos[index].last_meal_mutex);
	do_something(start_time, args->eat_t);
	pthread_mutex_unlock(&left_fork->fork_mutex);
	pthread_mutex_unlock(&right_fork->fork_mutex);
	update_meal_info(philos, index);
	return (TRUE);
}
