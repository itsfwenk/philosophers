/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:12:51 by fli               #+#    #+#             */
/*   Updated: 2024/07/26 15:27:55 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	dish_washer(t_arg *args)
{
	int	i;

	i = 0;
	while (i < args->n_philo)
	{
		pthread_mutex_destroy(&args->forks[i].fork_mutex);
		i++;
	}
}

void	detach_philo(t_arg *args)
{
	int	i;

	i = 0;
	while (args->philos[i].exist == TRUE)
	{
		pthread_detach(args->philos[i].tid);
		i++;
	}
}
