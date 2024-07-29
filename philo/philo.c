/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:17:50 by fli               #+#    #+#             */
/*   Updated: 2024/07/29 18:17:24 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	create_philo(t_arg *args, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < args->n_philo)
	{
		philos[i].exist = TRUE;
		philos[i].name = i + 1;
		philos[i].right_fork = i;
		if (i == 0)
			philos[i].left_fork = args->n_philo - 1;
		else
			philos[i].left_fork = i - 1;
		pthread_mutex_init(&philos[i].n_meal_mutex, NULL);
		pthread_mutex_lock(&philos[i].n_meal_mutex);
		philos[i].n_meal = 0;
		pthread_mutex_unlock(&philos[i].n_meal_mutex);
		pthread_mutex_lock(&args->current_mutex);
		args->current = i;
		pthread_mutex_unlock(&args->current_mutex);
		pthread_mutex_init(&philos[i].last_meal_mutex, NULL);
		pthread_mutex_lock(&philos[i].last_meal_mutex);
		philos[i].last_meal = get_time_ms();
		pthread_mutex_unlock(&philos[i].last_meal_mutex);
		start_philo(args);
		i++;
	}
}

static void	init_forks(t_arg *args, t_fork	*forks)
{
	int	i;

	i = 0;
	while (i < args->n_philo)
	{
		forks[i].belong_to = i + 1;
		pthread_mutex_init(&forks[i].fork_mutex, NULL);
		i++;
	}
	i = 0;
	// while (i < args->n_philo)
	// {
	// 	dprintf(2, "belong to %d\n", forks[i].belong_to);
	// 	i++;
	// }
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
	forks = malloc((1 + ft_atoi(av[1])) * sizeof(t_fork));
	if (forks == NULL)
		return (free(philos), FALSE);
	args.forks = forks;
	init_forks(&args, forks);
	create_philo(&args, philos);
	join_philo(philos);
}
