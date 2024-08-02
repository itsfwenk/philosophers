/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dessert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:44:06 by fli               #+#    #+#             */
/*   Updated: 2024/08/02 17:51:55 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_dessert(void *args)
{
	int		i;
	t_arg	*arg;

	arg = (t_arg *)args;
	i = 0;
	while (i < arg->n_philo)
	{
		sem_wait(arg->dessert);
		i++;
	}
	kill(arg->philos[0].pid, SIGINT);
	return (NULL);
}

void	launch_dessert(t_arg *args)
{
	if (args->min_meals == -1)
		return ;
	pthread_create(&(args->dessert_thread), NULL, check_dessert, args);
	pthread_detach(args->dessert_thread);
}
