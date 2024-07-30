/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:12:51 by fli               #+#    #+#             */
/*   Updated: 2024/07/30 21:53:45 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_detach(t_arg *args)
{
	int	i;

	i = 0;
	while (args->philos[i].exist == TRUE)
	{
		pthread_mutex_destroy(&args->philos[i].n_meal_mutex);
		pthread_mutex_destroy(&args->philos[i].alive_mutex);
		pthread_mutex_destroy(&args->philos[i].last_meal_mutex);
		// pthread_detach(args->philos[i].tid);
		i++;
	}
	i = 0;
	while (i < args->n_philo)
	{
		pthread_mutex_destroy(&args->forks[i].fork_mutex);
		i++;
	}
	pthread_mutex_destroy(&args->current_mutex);
	pthread_mutex_destroy(&args->talking_stick);
}

void	until_end(t_arg *args, t_philo *philos)
{
	int	i;

	// dprintf(1, "////////////////////");
	while (TRUE)
	{
		i = 0;
		// dprintf(2, "////////////////////");
		while (i < args->n_philo)
		{
			pthread_mutex_lock(&philos[i].alive_mutex);
			if (philos[i].alive == FALSE || check_meals(args, philos) == TRUE)
			{
				
				destroy_detach(args);
				free(philos);
				free(args->forks);
				int j = 0;
				while (j < args->n_philo)
				{
					dprintf(2, "meals eating : %d\n", philos[j].n_meal);
					j++;
				}
				exit(EXIT_SUCCESS);
			}
			pthread_mutex_unlock(&philos[i].alive_mutex);
			i++;
		}
	}
}
