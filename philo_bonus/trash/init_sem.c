/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 23:09:26 by fli               #+#    #+#             */
/*   Updated: 2024/08/01 23:13:17 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	init_fork(t_arg *args)
{
	sem_unlink("/philo_forks");
	args->forks = sem_open("/philo_forks", O_CREAT, S_IRWXU, args->n_philo);
	if (args->forks == SEM_FAILED)
	{
		sem_close(args->dessert);
		sem_unlink("/philo_dessert");
		sem_close(args->armageddon);
		sem_unlink("/philo_armageddon");
		sem_close(args->talking_stick);
		sem_unlink("/philo_talking_stick");
		return ;
	}
}

void	init_semaphores(t_arg *args)
{
	sem_unlink("/philo_dessert");
	args->dessert = sem_open("/philo_dessert", O_CREAT, S_IRWXU, 200);
	if (args->armageddon == SEM_FAILED)
		return ;
	sem_unlink("/philo_armageddon");
	args->armageddon = sem_open("/philo_armageddon", O_CREAT, S_IRWXU, 1);
	if (args->dessert == SEM_FAILED)
	{
		sem_close(args->dessert);
		sem_unlink("/philo_dessert");
		return ;
	}
	sem_unlink("/philo_talking_stick");
	args->talking_stick = sem_open("/philo_talking_stick", O_CREAT, S_IRWXU, 1);
	if (args->talking_stick == SEM_FAILED)
	{
		sem_close(args->dessert);
		sem_unlink("/philo_dessert");
		sem_close(args->armageddon);
		sem_unlink("/philo_armageddon");
		return ;
	}
	init_fork(args);
	return ;
}
