/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 14:52:39 by fli               #+#    #+#             */
/*   Updated: 2024/07/31 16:32:05 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	fork_availability(t_arg *args, t_philo *philos, int index)
// {
// 	int		availability;
// 	t_fork	*left_fork;
// 	t_fork	*right_fork;

// 	availability = 0;
// 	left_fork = &(args->forks)[philos[index].left_fork];
// 	right_fork = &(args->forks)[philos[index].right_fork];
// 	pthread_mutex_lock(&args->check_forks);
// 	if (left_fork->available == TRUE)
// 		availability++;
// 	if (right_fork->available == TRUE)
// 		availability++;
// 	pthread_mutex_unlock(&args->check_forks);
// 	if (availability == 2)
// 		return (TRUE);
// 	else
// 		return (FALSE);
// }

// int	use_brain(t_arg *args, t_philo *philos, int index)
// {
// 	print_action(args, philos[index].name, "is thinking");
// }

// int	take_nap(t_arg *args, t_philo *philos, int index)
// {
// 	print_action(args, philos[index].name, "is sleeping");
// 	do_something(args->sleep_t);
// 	// if (check_alive(args, philos, index) == FALSE)
// 	// 	return (FALSE);
// 	return (TRUE);
// }