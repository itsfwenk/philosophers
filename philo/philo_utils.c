/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:47:21 by fli               #+#    #+#             */
/*   Updated: 2024/07/24 17:28:32 by fli              ###   ########.fr       */
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

int	check_alive(t_arg *args, t_philo **philos, int name)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	if (tp.tv_sec - philos[name]->last_meal > (args->die_t) / 1000)
	{
		free(args->forks);
		free(philos);
		printf("%ld %d died\n", time_from_start(args), name);
		exit(0);
	}
	else
		return (TRUE);
}
