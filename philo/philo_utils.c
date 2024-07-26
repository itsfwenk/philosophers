/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:47:21 by fli               #+#    #+#             */
/*   Updated: 2024/07/26 14:08:15 by fli              ###   ########.fr       */
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
	args->n_philo = ft_atoi(av[1]);
	args->die_t = ft_atoi(av[2]);
	args->eat_t = ft_atoi(av[3]);
	args->sleep_t = ft_atoi(av[4]);
	args->min_meals = ft_atoi(av[5]);
	args->start_time = get_time_ms();
	args->forks = NULL;
}

suseconds_t	get_time_ms(void)
{
	struct timeval	tp;
	suseconds_t		current_time;

	gettimeofday(&tp, NULL);
	// printf("sec time %ld\n", tp.tv_sec);
	// printf("usec time %ld\n", tp.tv_usec);
	current_time = ((tp.tv_sec * 1000000) + tp.tv_usec) / 1000;
	return (current_time);
}

time_t	time_from_start(t_arg *args)
{
	suseconds_t	current_time;

	current_time = get_time_ms();
	// printf("current time %ld\n", current_time);
	// printf("start time %ld\n", args->start_time);
	return (current_time - args->start_time);
}
