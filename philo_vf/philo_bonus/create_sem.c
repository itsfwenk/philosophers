/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_sem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:50:12 by fli               #+#    #+#             */
/*   Updated: 2024/08/06 14:54:06 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	init_cutlery(t_arg *args)
{
	sem_unlink("/philo_cutlery");
	args->cutlery = sem_open("/philo_cutlery", O_CREAT, S_IRWXU, 1);
	if (args->forks == SEM_FAILED)
	{
		sem_close(args->dessert);
		sem_unlink("/philo_dessert");
		sem_close(args->armageddon);
		sem_unlink("/philo_armageddon");
		sem_close(args->talking_stick);
		sem_unlink("/philo_talking_stick");
		sem_close(args->forks);
		sem_unlink("/philo_forks");
		return (FALSE);
	}
	return (TRUE);
}

static int	init_fork(t_arg *args)
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
		return (FALSE);
	}
	if (init_cutlery(args) == FALSE)
		return (FALSE);
	return (TRUE);
}

int	init_semaphores(t_arg *args)
{
	sem_unlink("/philo_dessert");
	args->dessert = sem_open("/philo_dessert", O_CREAT, S_IRWXU, 200);
	if (args->dessert == SEM_FAILED)
		return (FALSE);
	sem_unlink("/philo_armageddon");
	args->armageddon = sem_open("/philo_armageddon", O_CREAT, S_IRWXU, 1);
	if (args->dessert == SEM_FAILED)
	{
		sem_close(args->dessert);
		sem_unlink("/philo_dessert");
		return (FALSE);
	}
	sem_unlink("/philo_talking_stick");
	args->talking_stick = sem_open("/philo_talking_stick", O_CREAT, S_IRWXU, 1);
	if (args->talking_stick == SEM_FAILED)
	{
		sem_close(args->dessert);
		sem_unlink("/philo_dessert");
		sem_close(args->armageddon);
		sem_unlink("/philo_armageddon");
		return (FALSE);
	}
	if (init_fork(args) == FALSE)
		return (FALSE);
	return (TRUE);
}
