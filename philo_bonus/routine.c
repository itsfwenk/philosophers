/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 22:48:43 by fli               #+#    #+#             */
/*   Updated: 2024/08/01 19:03:18 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	do_something(int waiting_time)
{
	suseconds_t		starting_time;

	starting_time = get_time_ms();
	while ((get_time_ms() - starting_time) < (waiting_time))
	{
		usleep(10);
	}
}

// static void	*one_philo_routine(t_arg *args, t_philo *philos, int index)
// {
// 	int		index;
// 	t_philo	*philos;

// 	philos = ((t_arg *)args)->philos;
// 	index = ((t_arg *)args)->current;
// 	pthread_mutex_unlock(&((t_arg *)args)->current_mutex);
// 	print_action(args, philos[index].name, "is thinking");
// 	seize_fork(&((t_arg *)args)->forks[0], args, philos, index);
// 	do_something(((t_arg *)args)->die_t);
// 	print_action(args, philos[index].name, "died");
// 	pthread_mutex_lock(&((t_arg *)args)->armageddon_mutex);
// 	((t_arg *)args)->armageddon = TRUE;
// 	pthread_mutex_unlock(&((t_arg *)args)->armageddon_mutex);
// 	return (NULL);
// }

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

	i = ((t_arg *)args)->current;
	philos = ((t_arg *)args)->philos;
	check_frequency = optimal_frequency(args);
	while (TRUE)
	{
		sem_wait(((t_arg *)args)->armageddon);
		if ((get_time_ms() - philos[i].last_meal) > ((t_arg *)args)->die_t)
		{
			print_action(((t_arg *)args), philos[i].name, "died");
			((t_arg *)args)->stop_dinner = TRUE;
			sem_wait(((t_arg *)args)->talking_stick);
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
	if (index + 1 % 2 != 0)
		do_something(args->eat_t);
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
	free(philos);
	exit(EXIT_SUCCESS);
}

void	start_philo(t_arg *args, t_philo *philos, int index)
{
	if (args->n_philo == 1)
		one_philo_routine(args, philos, index);
	else
		philo_routine(args, philos, index);
}
