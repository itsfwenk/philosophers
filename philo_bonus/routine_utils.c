/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:48:47 by fli               #+#    #+#             */
/*   Updated: 2024/08/02 01:10:59 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	do_something(int waiting_time)
{
	time_t		starting_time;

	starting_time = get_time_ms();
	while ((get_time_ms() - starting_time) < (waiting_time))
	{
		usleep(10);
	}
}

void	eat_spaghet(t_arg *args, t_philo *philos, int index)
{
	sem_wait(args->forks);
	print_action(args, philos[index].name, "has taken a fork");
	sem_wait(args->forks);
	print_action(args, philos[index].name, "has taken a fork");
	sem_wait(args->armageddon);
	philos[index].last_meal = get_time_ms();
	sem_post(args->armageddon);
	print_action(args, philos[index].name, "is eating");
	do_something(args->eat_t);
	sem_post(args->forks);
	sem_post(args->forks);
	(philos[index].n_meal)++;
	if (philos[index].n_meal == args->min_meals)
		sem_post(args->dessert);
}

void	take_nap(t_arg *args, t_philo *philos, int index)
{
	print_action(args, philos[index].name, "is sleeping");
	do_something(args->sleep_t);
}