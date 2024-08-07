/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:17:50 by fli               #+#    #+#             */
/*   Updated: 2024/08/06 14:50:58 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
