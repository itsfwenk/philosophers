/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 22:48:43 by fli               #+#    #+#             */
/*   Updated: 2024/07/30 19:56:37 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	do_something(int waiting_time)
{
	suseconds_t		starting_time;

	starting_time = get_time_ms();
	while ((get_time_ms() - starting_time) < (waiting_time))
	{
		usleep(400);
	}
}

void	*philo_routine(void *args)
{
	int		index;
	t_philo	*philos;

	philos = ((t_arg *)args)->philos;
	index = ((t_arg *)args)->current;
	// pthread_mutex_lock(&((t_arg *)args)->talking_stick);//
	// dprintf(2, "PHILO CURRENT IS %d\n", index);//
	// pthread_mutex_unlock(&((t_arg *)args)->talking_stick);//
	pthread_mutex_unlock(&((t_arg *)args)->current_mutex);
	while (check_alive(args, philos, index) == TRUE)
	{
		use_brain(((t_arg *)args), philos, index);
		if (eat_spaghet(((t_arg *)args), philos, index) == FALSE)
			break ;
		if (take_nap(((t_arg *)args), philos, index) == FALSE)
			break ;
	}
	return (NULL);
}

void	start_philo(t_arg *args)
{
	pthread_t	*current_tid;

	current_tid = &args->philos[args->current].tid;
	pthread_create(current_tid, NULL, philo_routine, args);
	// printf("tid = %ld\n", current_tid);
}