/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:17:50 by fli               #+#    #+#             */
/*   Updated: 2024/07/25 16:28:20 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	create_philo(t_arg *args, t_philo **philos)
{
	int	i;

	i = 0;
	args->philos = philos;
	while (i < args->n_philo)
	{
		philos[i]->exist = TRUE;
		philos[i]->name = i + 1;
		philos[i]->right_fork = i;
		if (i == 0)
			philos[i]->left_fork = args->n_philo - 1;
		else
			philos[i]->left_fork = i - 1;
		philos[i]->last_meal = 0;
		philos[i]->n_meal = 0;
		args->current = philos[i]->name;
		start_philo(args);
		i++;
	}
	philos[i] = NULL;
}

static void	init_forks(t_arg *args, t_fork	**forks)
{
	int	i;

	i = 0;
	while (i < args->n_philo)
	{
		forks[i]->belong_to = i + 1;
		pthread_mutex_init(&forks[i]->fork_mutex, NULL);
		i++;
	}
}

static void	init_philo(t_arg *args, t_philo **philos)
{
	int	i;

	i = 0;
	while (i < args->n_philo)
	{
		(*philos)[i].exist = FALSE;
		i++;
	}
}

int	main(int ac, char **av)
{
	t_arg	args;
	t_philo	*philos;
	t_fork	*forks;

	(void)ac;
	get_args(av, &args);
	philos = malloc((1 + ft_atoi(av[1])) * sizeof(t_philo));
	if (philos == NULL)
		return (FALSE);
	args.philos = &philos;
	init_philo(&args, &philos);
	forks = malloc((1 + ft_atoi(av[1])) * sizeof(t_fork));
	if (forks == NULL)
		return (free(philos), FALSE);
	args.forks = &forks;
	init_forks(&args, &forks);
	create_philo(&args, &philos);
}
