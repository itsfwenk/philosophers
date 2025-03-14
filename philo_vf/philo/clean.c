/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:12:51 by fli               #+#    #+#             */
/*   Updated: 2024/08/06 15:18:46 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_forks_mutex(t_arg *args, t_fork	*forks)
{
	int	i;

	i = 0;
	while (i < args->n_philo)
	{
		pthread_mutex_destroy(&forks[i].fork_mutex);
		i++;
	}
}

static void	destroy_philos_mutex(t_arg *args, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < args->n_philo)
	{
		pthread_mutex_destroy(&philos[i].n_meal_mutex);
		pthread_mutex_destroy(&philos[i].last_meal_mutex);
		i++;
	}
}

void	destroy_mutexes(t_arg *args, t_fork	*forks, t_philo *philos)
{
	destroy_forks_mutex(args, forks);
	destroy_philos_mutex(args, philos);
	pthread_mutex_destroy(&args->current_mutex);
	pthread_mutex_destroy(&args->armageddon_mutex);
	pthread_mutex_destroy(&args->talking_stick);
}

void	until_end(t_arg *args, t_philo *philos)
{
	int	i;

	while (TRUE)
	{
		i = 0;
		while (i < args->n_philo)
		{
			if (check_alive(args, philos, i) == FALSE
				|| check_meals(args, philos) == TRUE)
				return ;
			i++;
		}
		usleep(1000);
	}
}

void	join_philo(t_arg *args, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < args->n_philo)
	{
		pthread_join(philos[i].tid, NULL);
		i++;
	}
}
