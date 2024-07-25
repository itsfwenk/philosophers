/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:47:21 by fli               #+#    #+#             */
/*   Updated: 2024/07/25 15:14:49 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *s)
{
	int	i;
	int	res;

	res = 0;
	i = 0;
	while (s[i] != '\0')
	{
		res = res * 10;
		res = res + (s[i] - '0');
		i++;
	}
	return (res);
}

void	get_args(char **av, t_arg *args)
{
	struct timeval	tp;

	args->n_philo = ft_atoi(av[1]);
	args->die_t = ft_atoi(av[2]);
	args->eat_t = ft_atoi(av[3]);
	args->sleep_t = ft_atoi(av[4]);
	args->min_meals = ft_atoi(av[5]);
	gettimeofday(&tp, NULL);
	args->start_time = tp.tv_sec / 1000;
	args->forks = NULL;
}

time_t	time_from_start(t_arg *args)
{
	struct timeval	tp;
	time_t			current_time;

	gettimeofday(&tp, NULL);
	current_time = tp.tv_sec / 1000;
	return (current_time - args->start_time);
}
