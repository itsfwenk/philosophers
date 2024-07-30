/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mother.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 19:03:47 by fli               #+#    #+#             */
/*   Updated: 2024/07/30 15:08:06 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philo_mutex(t_philo *philos, int index)
{
	pthread_mutex_init(&philos[index].n_meal_mutex, NULL);
	pthread_mutex_lock(&philos[index].n_meal_mutex);
	philos[index].n_meal = 0;
	pthread_mutex_unlock(&philos[index].n_meal_mutex);
	pthread_mutex_init(&philos[index].last_meal_mutex, NULL);
	pthread_mutex_lock(&philos[index].last_meal_mutex);
	philos[index].last_meal = get_time_ms();
	pthread_mutex_unlock(&philos[index].last_meal_mutex);
	pthread_mutex_init(&philos[index].alive_mutex, NULL);
	pthread_mutex_lock(&philos[index].alive_mutex);
	philos[index].alive = TRUE;
	pthread_mutex_unlock(&philos[index].alive_mutex);
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
		init_philo_mutex(philos, i);
		pthread_mutex_lock(&args->current_mutex);
		args->current = i;
		start_philo(args);
		i++;
	}
}
