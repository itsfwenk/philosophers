/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:30:32 by fli               #+#    #+#             */
/*   Updated: 2024/07/30 19:46:26 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_alive(t_arg *args, t_philo *philos, int index)
{
	// printf("current time %ld\nlast meal %ld\n", get_time_ms(), philos[index].last_meal);
	// printf("since last meal %ld\n", get_time_ms() - philos[index].last_meal);
	// printf("time to die %d\n", args->die_t);
	pthread_mutex_lock(&philos[index].last_meal_mutex);
	if ((get_time_ms() - philos[index].last_meal) > args->die_t)
	{
		pthread_mutex_lock(&philos[index].alive_mutex);
		philos[index].alive = FALSE;
		pthread_mutex_unlock(&philos[index].alive_mutex);
		printf("%ld %d died\n", time_from_start(args), philos[index].name);
		pthread_mutex_unlock(&philos[index].last_meal_mutex);
		return (FALSE);
	}
	pthread_mutex_unlock(&philos[index].last_meal_mutex);
	return (TRUE);
}

int	count_philo(t_arg *args)
{
	int	i;

	i = 0;
	while (args->philos[i].exist == TRUE)
	{
		i++;
	}
	return (i);
}

int	check_meals(t_arg *args, t_philo *philos)
{
	int	i;
	if (count_philo(args) != args->n_philo)
		return (FALSE);
	if (args->min_meals == -1)
		return (FALSE);
	i = 0;
	while (philos[i].exist == TRUE)
	{
		pthread_mutex_lock(&philos[i].n_meal_mutex);
		if (philos[i].n_meal < args->min_meals)
		{
			pthread_mutex_unlock(&philos[i].n_meal_mutex);
			return (FALSE);
		}
		pthread_mutex_unlock(&philos[i].n_meal_mutex);
		i++;
	}
	return (TRUE);
}

void	join_philo(t_philo *philos)
{
	int	i;

	i = 0;
	while (philos[i].exist == TRUE)
	{
		pthread_join(philos[i].tid, NULL);
		i++;
	}
}

void	philo_id(t_arg *args)
{
	t_philo current_philo;

	current_philo = args->philos[args->current];
	printf("////////////////////////////////////\n");
	printf("name %d\n", current_philo.name);
	printf("left fork %d\n", current_philo.left_fork);
	printf("right fork %d\n", current_philo.right_fork);
	printf("eaten meals %d\n", current_philo.n_meal);
	printf("exist %d\n", current_philo.exist);
	printf("last meal %ld\n", current_philo.last_meal);
	printf("tid %lu\n", (unsigned long)current_philo.tid);
	printf("////////////////////////////////////\n");
}

void	print_args(t_arg *args)
{
	printf("##############################################\n");
	printf("nb philo %d\n", args->n_philo);
	printf("die time %d\n", args->die_t);
	printf("eat time %d\n", args->eat_t);
	printf("sleep time %d\n", args->sleep_t);
	printf("min meals %d\n", args->min_meals);
	printf("current %d\n", args->current);
	printf("start time %ld\n", args->start_time);
	printf("##############################################\n");
}

void	show_all_philo(t_arg *args)
{
	int	i = 0;
	t_philo	current_philo;
	dprintf(2, "ALL PHILO");
	while (((t_arg *)args)->n_philo)
	{
	current_philo = args->philos[i];
	printf("////////////////////////////////////\n");
	printf("name %d\n", current_philo.name);
	printf("left fork %d\n", current_philo.left_fork);
	printf("right fork %d\n", current_philo.right_fork);
	printf("eaten meals %d\n", current_philo.n_meal);
	printf("exist %d\n", current_philo.exist);
	printf("last meal %ld\n", current_philo.last_meal);
	printf("tid %lu\n", (unsigned long)current_philo.tid);
	printf("////////////////////////////////////\n");
	}
}
