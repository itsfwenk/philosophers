/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 22:48:43 by fli               #+#    #+#             */
/*   Updated: 2024/08/02 01:09:35 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	*one_philo_routine(t_arg *args, t_philo *philos)
{
	print_action(args, philos[0].name, "is thinking");
	sem_wait(args->forks);
	print_action(args, philos[0].name, "has taken a fork");
	do_something(args->die_t);
	print_action(args, philos[0].name, "died");
	return (NULL);
}

int	check_stop(t_arg *args)
{
	sem_wait(args->armageddon);
	if (args->stop_dinner == TRUE)
	{
		sem_post(args->armageddon);
		return (TRUE);
	}
	else
	{
		sem_post(args->armageddon);
		return (FALSE);
	}
}

void	*check_death(void *args)
{
	int		check_frequency;
	int		i;
	t_philo	*philos;
	t_arg	*arg;

	arg = ((t_arg *)args);
	i = ((t_arg *)args)->current;
	philos = ((t_arg *)args)->philos;
	check_frequency = optimal_frequency(args);
	while (TRUE)
	{
		sem_wait(((t_arg *)args)->armageddon);
		if ((get_time_ms() - philos[i].last_meal) > ((t_arg *)args)->die_t)
		{
			((t_arg *)args)->stop_dinner = TRUE;
			sem_wait(arg->talking_stick);
			printf("%ld %d died\n", time_from_start(arg), philos[i].name);
			sem_post(((t_arg *)args)->armageddon);
			// sem_post(arg->talking_stick);
			exit(EXIT_SUCCESS);
		}
		sem_post(((t_arg *)args)->armageddon);
		usleep(check_frequency * 1000);
	}
}

void	philo_routine(t_arg *args, t_philo *philos, int index)
{
	philos[index].last_meal = get_time_ms();
	pthread_create(&(philos[index].tid), NULL, check_death, args);
	// if ((index + 1) % 2 != 0)
	// 	do_something(100);
	while (TRUE)
	{
		print_action(args, philos[index].name, "is thinking");
		if (check_stop(args) == TRUE)
			break ;
		eat_spaghet(((t_arg *)args), philos, index);
		if (check_stop(args) == TRUE)
			break ;
		take_nap(((t_arg *)args), philos, index);
		if (check_stop(args) == TRUE)
			break ;
	}
	printf("%d exited\n", index + 1);
	exit(EXIT_SUCCESS);
}

void	start_philo(t_arg *args, t_philo *philos, int index)
{
	if (args->n_philo == 1)
		one_philo_routine(args, philos);
	else
		philo_routine(args, philos, index);
}
