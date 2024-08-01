/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mother.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 19:03:47 by fli               #+#    #+#             */
/*   Updated: 2024/08/02 01:06:23 by fli              ###   ########.fr       */
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
	kill(arg->philos[0].pid, SIGTERM);
	return (NULL);
}

void	launch_dessert(t_arg *args)
{
	if (args->min_meals == -1)
		return ;
	pthread_create(&(args->dessert_thread), NULL, check_dessert, args);
}

void	destroy_sem(t_arg *args)
{
	sem_close(args->dessert);
	sem_close(args->armageddon);
	sem_close(args->talking_stick);
	sem_close(args->forks);
	sem_unlink("/philo_dessert");
	sem_unlink("/philo_armageddon");
	sem_unlink("/philo_talking_stick");
	sem_unlink("/philo_forks");
}

void	wait_philos(t_arg *args)
{
	int		i;
	pid_t	dead_child;

	dead_child = waitpid(-1, NULL, 0);
	// sem_post(args->talking_stick);
	i = 0;
	while (i < args->n_philo && args->n_philo != 1)
	{
		if (args->philos[i].pid == dead_child)
		{
			i++;
			continue ;
		}
		else
		{
			kill(args->philos[i].pid, SIGTERM);
			i++;
		}
	}
	destroy_sem(args);
}

int	create_philo(t_arg *args, t_philo *philos)
{
	int	i;
	int	j;

	args->start_time = get_time_ms();
	i = 0;
	while (i < args->n_philo)
	{
		philos[i].pid = fork();
		if (philos[i].pid < 0)
		{
			j = 0;
			while (j < i)
			{
				kill(args->philos[i].pid, SIGTERM);
				j++;
			}
			return (FALSE);
		}
		if (philos[i].pid == 0)
		{
			args->current = i;
			start_philo(args, philos, i);
		}
		i++;
	}
	return (TRUE);
}
