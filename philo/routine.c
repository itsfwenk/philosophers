/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:48:47 by fli               #+#    #+#             */
/*   Updated: 2024/07/29 14:31:53 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static void	take_fork(t_arg *args, t_philo *philos, int name)
// {
// 	t_fork			*left_fork;
// 	t_fork			*right_fork;

// 	// philo_id(args);
// 	left_fork = &(args->forks)[philos[name].left_fork];
// 	right_fork = &(args->forks)[philos[name].right_fork];
// 	check_alive(args, philos, name);
// 	pthread_mutex_lock(&left_fork->fork_mutex);
// 	// dprintf(2, "current philo is %d\n", (name + 1));
// 	// dprintf(2, "left fork belongs to %d\n", left_fork->belong_to);
// 	printf("%ld %d has taken a fork\n", time_from_start(args), philos[name].name);
// 	check_alive(args, philos, name);
// 	pthread_mutex_lock(&right_fork->fork_mutex);
// 	// dprintf(2, "right fork belongs to %d\n", right_fork->belong_to);
// 	printf("%ld %d has taken a fork\n", time_from_start(args), philos[name].name);
// 	printf("%ld %d is eating\n", time_from_start(args), philos[name].name);
// 	philos[name].n_meal = (philos[name].n_meal) + 1;
// 	// dprintf(2, "hi\n");
// 	usleep(((args->eat_t) * 1000));
// 	// dprintf(2, "*********oi\n");
// 	philos[name].last_meal = get_time_ms();
// 	pthread_mutex_unlock(&left_fork->fork_mutex);
// 	pthread_mutex_unlock(&right_fork->fork_mutex);
// }

static void	take_fork(t_arg *args, t_philo *philos, int name)
{
	t_fork			*left_fork;
	t_fork			*right_fork;

	// philo_id(args);
	left_fork = &(args->forks)[philos[name].left_fork];
	right_fork = &(args->forks)[philos[name].right_fork];
	check_alive(args, philos, name);
	if ((name + 1) % 2 == 0)
	{
		pthread_mutex_lock(&right_fork->fork_mutex);
		// dprintf(2, "right fork belongs to %d\n", right_fork->belong_to);
		printf("%ld %d has taken a fork\n", time_from_start(args), philos[name].name);

		pthread_mutex_lock(&left_fork->fork_mutex);
		// dprintf(2, "current philo is %d\n", (name + 1));
		// dprintf(2, "left fork belongs to %d\n", left_fork->belong_to);
		printf("%ld %d has taken a fork\n", time_from_start(args), philos[name].name);
	}
	else
	{
		pthread_mutex_lock(&left_fork->fork_mutex);
		// dprintf(2, "current philo is %d\n", (name + 1));
		// dprintf(2, "left fork belongs to %d\n", left_fork->belong_to);
		printf("%ld %d has taken a fork\n", time_from_start(args), philos[name].name);

		pthread_mutex_lock(&right_fork->fork_mutex);
		// dprintf(2, "right fork belongs to %d\n", right_fork->belong_to);
		printf("%ld %d has taken a fork\n", time_from_start(args), philos[name].name);
	}
	printf("%ld %d is eating\n", time_from_start(args), philos[name].name);
	usleep(((args->eat_t) * 1000));
	pthread_mutex_lock(&philos[name].n_meal_mutex);
	philos[name].n_meal = (philos[name].n_meal) + 1;
	pthread_mutex_unlock(&philos[name].n_meal_mutex);
	pthread_mutex_lock(&philos[name].last_meal_mutex);
	philos[name].last_meal = get_time_ms();
	pthread_mutex_unlock(&philos[name].last_meal_mutex);
	pthread_mutex_unlock(&left_fork->fork_mutex);
	pthread_mutex_unlock(&right_fork->fork_mutex);
}

static void	take_nap(t_arg *args, t_philo *philos, int name)
{
	printf("%ld %d is sleeping\n", time_from_start(args), philos[name].name);
	usleep((args->sleep_t) * 1000);
	check_alive(args, philos, name);
	printf("%ld %d is thinking\n", time_from_start(args), philos[name].name);
}

void	*philo_routine(void *args)
{
	int		index;
	t_philo	*philos;

	philos = ((t_arg *)args)->philos;
	index = ((t_arg *)args)->current;
	while (check_meals(args, philos) == FALSE)
	{
		take_fork(((t_arg *)args), philos, index);
		take_nap(((t_arg *)args), philos, index);
	}
	dprintf(2, "end\n");
	show_all_philo(args);
	detach_philo(args);
	dish_washer(args);
	return (NULL);
}

void	start_philo(t_arg *args)
{
	pthread_t	current_tid;

	current_tid = args->philos[args->current].tid;
	pthread_create(&current_tid, NULL, philo_routine, args);
	// printf("tid = %ld\n", current_tid);
}
