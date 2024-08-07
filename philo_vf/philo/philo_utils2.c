/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:30:32 by fli               #+#    #+#             */
/*   Updated: 2024/08/06 15:20:23 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_alive(t_arg *args, t_philo *philos, int index)
{
	pthread_mutex_lock(&args->armageddon_mutex);
	if (args->armageddon == TRUE)
	{
		pthread_mutex_unlock(&args->armageddon_mutex);
		return (FALSE);
	}
	pthread_mutex_unlock(&args->armageddon_mutex);
	pthread_mutex_lock(&philos[index].last_meal_mutex);
	if ((get_time_ms() - philos[index].last_meal) > args->die_t)
	{
		print_action(args, philos[index].name, "died");
		pthread_mutex_lock(&args->armageddon_mutex);
		args->armageddon = TRUE;
		pthread_mutex_unlock(&args->armageddon_mutex);
		pthread_mutex_unlock(&philos[index].last_meal_mutex);
		return (FALSE);
	}
	pthread_mutex_unlock(&philos[index].last_meal_mutex);
	return (TRUE);
}

int	check_meals(t_arg *args, t_philo *philos)
{
	int	i;

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
	pthread_mutex_lock(&args->armageddon_mutex);
	args->armageddon = TRUE;
	pthread_mutex_unlock(&args->armageddon_mutex);
	return (TRUE);
}

int	take_nap(t_arg *args, t_philo *philos, int index)
{
	suseconds_t	start;

	start = get_time_ms();
	print_action(args, philos[index].name, "is sleeping");
	do_something(start, args->sleep_t);
	return (TRUE);
}
