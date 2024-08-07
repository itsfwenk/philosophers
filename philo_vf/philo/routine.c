/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 22:48:43 by fli               #+#    #+#             */
/*   Updated: 2024/08/02 17:39:11 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	do_something(suseconds_t start, int waiting_time)
{
	while ((get_time_ms() - start) < (suseconds_t)(waiting_time))
	{
		usleep(10);
	}
}

static int	check_armageddon(t_arg *args)
{
	pthread_mutex_lock(&args->armageddon_mutex);
	if (((t_arg *)args)->armageddon == TRUE)
	{
		pthread_mutex_unlock(&args->armageddon_mutex);
		return (TRUE);
	}
	pthread_mutex_unlock(&args->armageddon_mutex);
	return (FALSE);
}

void	*philo_routine(void *args)
{
	int		index;
	t_philo	*philos;

	pthread_mutex_lock(&((t_arg *)args)->current_mutex);
	index = ((t_arg *)args)->current;
	pthread_mutex_unlock(&((t_arg *)args)->current_mutex);
	philos = ((t_arg *)args)->philos;
	while (TRUE)
	{
		print_action(args, philos[index].name, "is thinking");
		if (check_armageddon(args) == TRUE)
			break ;
		eat_spaghet(((t_arg *)args), philos, index);
		if (check_armageddon(args) == TRUE)
			break ;
		take_nap(((t_arg *)args), philos, index);
		if (check_armageddon(args) == TRUE)
			break ;
	}
	return (NULL);
}

static void	*one_philo_routine(void *args)
{
	int			index;
	t_philo		*philos;
	suseconds_t	start;

	pthread_mutex_lock(&((t_arg *)args)->current_mutex);
	index = ((t_arg *)args)->current;
	pthread_mutex_unlock(&((t_arg *)args)->current_mutex);
	philos = ((t_arg *)args)->philos;
	print_action(args, philos[index].name, "is thinking");
	seize_fork(&((t_arg *)args)->forks[0], args, philos, index);
	start = get_time_ms();
	do_something(start, ((t_arg *)args)->die_t);
	print_action(args, philos[index].name, "died");
	pthread_mutex_lock(&((t_arg *)args)->armageddon_mutex);
	((t_arg *)args)->armageddon = TRUE;
	pthread_mutex_unlock(&((t_arg *)args)->armageddon_mutex);
	return (NULL);
}

void	start_philo(t_arg *args)
{
	pthread_t	*current_tid;

	current_tid = &args->philos[args->current].tid;
	if (args->n_philo == 1)
		pthread_create(current_tid, NULL, one_philo_routine, args);
	else
		pthread_create(current_tid, NULL, philo_routine, args);
}
