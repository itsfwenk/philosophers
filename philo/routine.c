/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 22:48:43 by fli               #+#    #+#             */
/*   Updated: 2024/07/29 22:51:05 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *args)
{
	int		index;
	t_philo	*philos;

	philos = ((t_arg *)args)->philos;
	index = ((t_arg *)args)->current;
	pthread_mutex_unlock(&((t_arg *)args)->current_mutex);
	while (check_alive(args, philos, index) == TRUE)
	{
		use_brain(((t_arg *)args), philos, index);
		eat_spaghet(((t_arg *)args), philos, index);
		take_nap(((t_arg *)args), philos, index);
	}
	return (NULL);
}

void	start_philo(t_arg *args)
{
	pthread_t	current_tid;

	pthread_mutex_lock(&args->current_mutex);
	current_tid = args->philos[args->current].tid;
	pthread_create(&current_tid, NULL, philo_routine, args);
	// printf("tid = %ld\n", current_tid);
}