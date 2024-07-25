/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:30:32 by fli               #+#    #+#             */
/*   Updated: 2024/07/25 16:44:45 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_alive(t_arg *args, t_philo **philos, int name)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	if (tp.tv_sec - (*philos)[name]->last_meal > (args->die_t) / 1000)
	{
		free(args->forks);
		free((*philos));
		printf("%ld %d died\n", time_from_start(args), name);
		exit(0);
	}
	else
		return (TRUE);
}

int	count_philo(t_arg *args)
{
	int	i;

	i = 0;
	while (args->philos[i]->exist == TRUE)
	{
		i++;
	}
	return (i);
}

int	check_meals(t_arg *args, t_philo **philos)
{
	int	i;

	if (count_philo(args) != args->n_philo)
		return (FALSE);
	i = 0;
	while (philos[i] != NULL)
	{
		if (philos[i]->n_meal < args->min_meals)
			return (FALSE);
		i++;
	}
	return (TRUE);
}
