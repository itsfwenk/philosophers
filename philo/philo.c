/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:17:50 by fli               #+#    #+#             */
/*   Updated: 2024/07/23 18:27:33 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	int		i;
	t_arg	philos;

	philos.n_philo = ft_atoi(av[1]);
	philos.die_t = ft_atoi(av[2]);
	philos.eat_t = ft_atoi(av[3]);
	philos.sleep_t = ft_atoi(av[4]);
	i = 0;
	while (i < philos.n_philo)
	{
		pthread_create(philos.thread, );
	}
}
