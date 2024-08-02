/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:17:50 by fli               #+#    #+#             */
/*   Updated: 2024/08/02 18:11:26 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	return (TRUE);
}

static int	init_semaphores(t_arg *args)
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

void	get_args(int ac, char **av, t_arg *args)
{
	int	i;

	args->n_philo = ft_atoi(av[1]);
	args->die_t = ft_atoi(av[2]);
	args->eat_t = ft_atoi(av[3]);
	args->sleep_t = ft_atoi(av[4]);
	if (ac == 6)
		args->min_meals = ft_atoi(av[5]);
	else
		args->min_meals = -1;
	args->current = 0;
	args->stop_dinner = FALSE;
	args->start_time = get_time_ms();
	if (init_semaphores(args) == FALSE)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < 200)
	{
		sem_wait(args->dessert);
		i++;
	}
}

static void	init_philo(t_arg *args, t_philo *philos)
{
	int		i;

	i = 0;
	while (i < args->n_philo)
	{
		philos[i].name = i + 1;
		philos[i].n_meal = 0;
		philos[i].last_meal = 0;
		i++;
	}
	args->philos = philos;
}

int	main(int ac, char **av)
{
	t_arg	args;
	t_philo	philos[200];

	if (check_arg(ac, av) == FALSE)
		exit(EXIT_SUCCESS);
	get_args(ac, av, &args);
	init_philo(&args, philos);
	if (create_philo(&args, philos) == FALSE)
	{
		destroy_sem(&args);
		exit(EXIT_FAILURE);
	}
	launch_dessert(&args);
	wait_philos(&args);
}
