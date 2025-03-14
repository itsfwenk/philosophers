/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:48:47 by fli               #+#    #+#             */
/*   Updated: 2024/08/06 14:41:54 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	do_something(time_t start, int waiting_time)
{
	while ((get_time_ms() - start) < (time_t)(waiting_time))
	{
		usleep(10);
	}
}

static void	pick_fork(t_arg *args, t_philo *philos, int index)
{
	sem_wait(args->cutlery);
	sem_wait(args->forks);
	print_action(args, philos[index].name, "has taken a fork");
	sem_wait(args->forks);
	print_action(args, philos[index].name, "has taken a fork");
	sem_post(args->cutlery);
}

void	eat_spaghet(t_arg *args, t_philo *philos, int index)
{
	time_t	start;

	pick_fork(args, philos, index);
	start = get_time_ms();
	sem_wait(args->armageddon);
	philos[index].last_meal = start;
	sem_post(args->armageddon);
	print_action(args, philos[index].name, "is eating");
	do_something(start, args->eat_t);
	sem_post(args->forks);
	sem_post(args->forks);
	(philos[index].n_meal)++;
	if (philos[index].n_meal == args->min_meals)
		sem_post(args->dessert);
}

void	take_nap(t_arg *args, t_philo *philos, int index)
{
	time_t	start;

	start = get_time_ms();
	print_action(args, philos[index].name, "is sleeping");
	do_something(start, args->sleep_t);
}
