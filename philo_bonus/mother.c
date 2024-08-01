/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mother.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 19:03:47 by fli               #+#    #+#             */
/*   Updated: 2024/08/01 19:33:53 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	wait_philos(t_arg *args)
{
	int		i;
	pid_t	dead_child;

	dead_child = waitpid(-1, NULL, 0);
	i = 0;
	while (i < args->n_philo)
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
	sem_close(args->armageddon);
	sem_close(args->talking_stick);
	sem_close(args->forks);
	sem_unlink("/philo_armageddon");
	sem_unlink("/philo_talking_stick");
	sem_unlink("/philo_forks");
}

int	create_philo(t_arg *args, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < args->n_philo)
	{
		philos[i].pid = fork();
		if (philos[i].pid < 0)
			return (FALSE);
		if (philos[i].pid == 0)
			start_philo(args, philos, i);
		i++;
	}
	return (TRUE);
}