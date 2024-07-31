/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:17:50 by fli               #+#    #+#             */
/*   Updated: 2024/07/31 17:31:39 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_forks(t_arg *args, t_fork	*forks)
{
	int	i;

	i = 0;
	while (i < args->n_philo)
	{
		pthread_mutex_init(&forks[i].fork_mutex, NULL);
		forks[i].belong_to = i + 1;
		// forks->available = TRUE;
		i++;
	}
}

static void	init_philo(t_arg *args, t_philo *philos)
{
	int	i;

	i = 0;
	while (i <= args->n_philo)
	{
		philos[i].exist = FALSE;
		i++;
	}
	args->philos = philos;
}

int	main(int ac, char **av)
{
	t_arg	args;
	t_philo	*philos;
	t_fork	*forks;

	get_args(ac, av, &args);
	// print_args(&args);
	philos = malloc((1 + args.n_philo) * sizeof(t_philo));
	if (philos == NULL)
		exit(EXIT_FAILURE);
	init_philo(&args, philos);
	forks = malloc((1 + args.n_philo) * sizeof(t_fork));
	if (forks == NULL)
		return (free(philos), FALSE);
	args.forks = forks;
	init_forks(&args, forks);
	create_philo(&args, philos);
	until_end(&args, philos);
	join_philo(&args, philos);
	destroy_mutexes(&args, forks, philos);
	free(philos);
	free(forks);
}

