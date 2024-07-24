/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:17:50 by fli               #+#    #+#             */
/*   Updated: 2024/07/24 14:45:35 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_philo(t_arg args, t_philo **philos)
{
	int	i;

	i = 0;
	while (i < args.n_philo)
	{
		philos[i]->name = i + 1;
		philos[i]->right_fork = i;
		if (i == 0)
			philos[i]->left_fork = args.n_philo - 1;
		else
			philos[i]->left_fork = i - 1;
		i++;
	}
	philos[i] = NULL;
}

int	main(int ac, char **av)
{
	t_arg	args;
	t_philo	*philos;
	t_fork	*forks;

	get_args(av, &args);
	philos = malloc((1 + ft_atoi(av[1])) * sizeof(t_philo));
	if (philos == NULL)
		return (NULL);
	forks = ((1 + ft_atoi(av[1])) * sizeof(t_fork));
	if (philos == NULL)
		return (free(philos), NULL);
	args.forks = forks;
	create_philo(args, philos);
}
