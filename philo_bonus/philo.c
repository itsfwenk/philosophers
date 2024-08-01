/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:17:50 by fli               #+#    #+#             */
/*   Updated: 2024/08/01 18:27:02 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	init_semaphores(t_arg *args)
{
	sem_unlink("/philo_armageddon");
	sem_unlink("/philo_talking_stick");
	sem_unlink("/philo_forks");
	args->armageddon = sem_open("/philo_armageddon", O_CREAT, S_IRWXU, 1);
	args->talking_stick = sem_open("/philo_talking_stick", O_CREAT, S_IRWXU, 1);
	args->forks = sem_open("/philo_forks", O_CREAT, S_IRWXU, args->n_philo);
	if (args->armageddon == SEM_FAILED
		|| args->talking_stick == SEM_FAILED || args->forks == SEM_FAILED)
		return (FALSE);
	return (TRUE);
}

void	get_args(int ac, char **av, t_arg *args)
{
	args->n_philo = ft_atoi(av[1]);
	args->die_t = ft_atoi(av[2]);
	args->eat_t = ft_atoi(av[3]);
	args->sleep_t = ft_atoi(av[4]);
	if (ac == 6)
		args->min_meals = ft_atoi(av[5]);
	else
		args->min_meals = -1;
	args->start_time = get_time_ms();
	init_semaphores(args);
}

static void	init_philo(t_arg *args, t_philo *philos)
{
	int	i;

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

	get_args(ac, av, &args);
	init_philo(&args, philos);
	create_philo(&args, philos);
	wait_philos(&args);
}

