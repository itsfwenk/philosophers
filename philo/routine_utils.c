/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:48:47 by fli               #+#    #+#             */
/*   Updated: 2024/07/31 19:42:40 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	seize_fork(t_fork *fork, t_arg *args, t_philo *philos, int i)
{
	// dprintf(2, "%d trying to take fork belonging to %d\n", philos[i].name, fork->belong_to);
	pthread_mutex_lock(&fork->fork_mutex);
	// if (check_alive(args, philos, i) == FALSE)
	// 	return (FALSE);
	print_action(args, philos[i].name, "has taken a fork");
	// dprintf(2, "took fork belonging to %d\n", fork->belong_to);
	// fork->available = FALSE;
	return (TRUE);
}

static int	take_forks(t_arg *args, t_philo *philos, int index)
{
	t_fork			*left_fork;
	t_fork			*right_fork;

	left_fork = &(args->forks)[philos[index].left_fork];
	right_fork = &(args->forks)[philos[index].right_fork];
	// if (check_alive(args, philos, index) == FALSE)
	// 	return (FALSE);
	// pthread_mutex_lock(&args->check_forks);
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
	// pthread_mutex_unlock(&args->check_forks);
	return (TRUE);
}

// static void	unlock_forks(t_arg *args, t_fork *left_fork, t_fork *right_fork)
// {
// 	// pthread_mutex_lock(&args->check_forks);
// 	pthread_mutex_unlock(&left_fork->fork_mutex);
// 	// left_fork->available = TRUE;
// 	pthread_mutex_unlock(&right_fork->fork_mutex);
// 	// right_fork->available = TRUE;
// 	// pthread_mutex_unlock(&args->check_forks);
// }

static void	update_meal_info(t_philo *philos, int index)
{
	pthread_mutex_lock(&philos[index].n_meal_mutex);
	philos[index].n_meal = (philos[index].n_meal) + 1;
	pthread_mutex_unlock(&philos[index].n_meal_mutex);
	// pthread_mutex_lock(&philos[index].last_meal_mutex);
	// philos[index].last_meal = get_time_ms();
	// pthread_mutex_unlock(&philos[index].last_meal_mutex);
}

int	eat_spaghet(t_arg *args, t_philo *philos, int index)
{
	t_fork			*left_fork;
	t_fork			*right_fork;

	left_fork = &(args->forks)[philos[index].left_fork];
	right_fork = &(args->forks)[philos[index].right_fork];
	if (take_forks(args, philos, index) == FALSE)
		return (FALSE);
	print_action(args, philos[index].name, "is eating");
	pthread_mutex_lock(&args->armageddon_mutex);
	pthread_mutex_lock(&philos[index].last_meal_mutex);
	philos[index].last_meal = get_time_ms();
	pthread_mutex_unlock(&args->armageddon_mutex);
	pthread_mutex_unlock(&philos[index].last_meal_mutex);
	do_something(args->eat_t);
	// unlock_forks(args, left_fork, right_fork);
	pthread_mutex_unlock(&left_fork->fork_mutex);
	pthread_mutex_unlock(&right_fork->fork_mutex);
	update_meal_info(philos, index);
	return (TRUE);
}

int	take_nap(t_arg *args, t_philo *philos, int index)
{
	print_action(args, philos[index].name, "is sleeping");
	do_something(args->sleep_t);
	// if (check_alive(args, philos, index) == FALSE)
	// 	return (FALSE);
	return (TRUE);
}