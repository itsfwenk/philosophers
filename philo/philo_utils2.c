/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:30:32 by fli               #+#    #+#             */
/*   Updated: 2024/08/02 17:41:00 by fli              ###   ########.fr       */
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

int	optimal_frequency(t_arg *args)
{
	int	min_cycle_time;
	int	max_wait_time;
	int	check_frequency;
	int	optimal_check_frequency;

	min_cycle_time = args->eat_t + args->sleep_t;
	max_wait_time = min_cycle_time + (args->eat_t - 1);
	check_frequency = max_wait_time / 2;
	if (check_frequency < args->die_t / 2)
		optimal_check_frequency = check_frequency;
	else
		optimal_check_frequency = (args->die_t / 2);
	return (optimal_check_frequency);
}

int	take_nap(t_arg *args, t_philo *philos, int index)
{
	suseconds_t	start;

	start = get_time_ms();
	print_action(args, philos[index].name, "is sleeping");
	do_something(start, args->sleep_t);
	return (TRUE);
}
