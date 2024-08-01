/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:30:32 by fli               #+#    #+#             */
/*   Updated: 2024/08/01 21:20:16 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// int	count_philo(t_arg *args)
// {
// 	int	i;

// 	i = 0;
// 	while (args->philos[i].exist == TRUE)
// 	{
// 		i++;
// 	}
// 	return (i);
// }

int	optimal_frequency(t_arg *args)
{
	int	min_cycle_time;
	int	max_wait_time;
	int	check_frequency;
	int	optimal_check_frequency;

	min_cycle_time = args->eat_t + args->sleep_t;
	max_wait_time = min_cycle_time + (args->eat_t - 1);
	check_frequency = max_wait_time / 2;
	if (check_frequency < args->die_t / 2)
		optimal_check_frequency = check_frequency;
	else
		optimal_check_frequency = (args->die_t / 2);
	return (optimal_check_frequency);
}

// void	philo_id(t_arg *args)
// {
// 	t_philo current_philo;

// 	current_philo = args->philos[args->current];
// 	printf("////////////////////////////////////\n");
// 	printf("name %d\n", current_philo.name);
// 	printf("left fork %d\n", current_philo.left_fork);
// 	printf("right fork %d\n", current_philo.right_fork);
// 	printf("eaten meals %d\n", current_philo.n_meal);
// 	printf("exist %d\n", current_philo.exist);
// 	printf("last meal %ld\n", current_philo.last_meal);
// 	printf("tid %lu\n", (unsigned long)current_philo.tid);
// 	printf("////////////////////////////////////\n");
// }

// void	print_args(t_arg *args)
// {
// 	printf("##############################################\n");
// 	printf("nb philo %d\n", args->n_philo);
// 	printf("die time %d\n", args->die_t);
// 	printf("eat time %d\n", args->eat_t);
// 	printf("sleep time %d\n", args->sleep_t);
// 	printf("min meals %d\n", args->min_meals);
// 	printf("current %d\n", args->current);
// 	printf("start time %ld\n", args->start_time);
// 	printf("##############################################\n");
// }

// void	show_all_philo(t_arg *args)
// {
// 	int	i = 0;
// 	t_philo	current_philo;
// 	dprintf(2, "ALL PHILO");
// 	while (((t_arg *)args)->n_philo)
// 	{
// 	current_philo = args->philos[i];
// 	printf("////////////////////////////////////\n");
// 	printf("name %d\n", current_philo.name);
// 	printf("left fork %d\n", current_philo.left_fork);
// 	printf("right fork %d\n", current_philo.right_fork);
// 	printf("eaten meals %d\n", current_philo.n_meal);
// 	printf("exist %d\n", current_philo.exist);
// 	printf("last meal %ld\n", current_philo.last_meal);
// 	printf("tid %lu\n", (unsigned long)current_philo.tid);
// 	printf("////////////////////////////////////\n");
// 	}
// }
