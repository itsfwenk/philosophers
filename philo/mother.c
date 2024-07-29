/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mother.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 19:03:47 by fli               #+#    #+#             */
/*   Updated: 2024/07/29 20:18:52 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_n_meal(t_philo *philos, int index)
{
	pthread_mutex_init(&philos[index].n_meal_mutex, NULL);
	pthread_mutex_lock(&philos[index].n_meal_mutex);
	philos[index].n_meal = 0;
	pthread_mutex_unlock(&philos[index].n_meal_mutex);
}

static void	init_last_meal(t_philo *philos, int index)
{
	pthread_mutex_init(&philos[index].last_meal_mutex, NULL);
	pthread_mutex_lock(&philos[index].last_meal_mutex);
	philos[index].last_meal = get_time_ms();
	pthread_mutex_unlock(&philos[index].last_meal_mutex);
}

static void	init_current(t_arg *args, int index)
{
	pthread_mutex_init(&args->current_mutex, NULL);
	pthread_mutex_lock(&args->current_mutex);
	args->current = index;
	pthread_mutex_unlock(&args->current_mutex);
}

void	create_philo(t_arg *args, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < args->n_philo)
	{
		philos[i].exist = TRUE;
		philos[i].name = i + 1;
		philos[i].right_fork = i;
		if (i == 0)
			philos[i].left_fork = args->n_philo - 1;
		else
			philos[i].left_fork = i - 1;
		init_n_meal(philos, i);
		init_last_meal(philos, i);
		init_current(args, i);
		start_philo(args);
		i++;
	}
}
