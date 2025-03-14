/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:47:21 by fli               #+#    #+#             */
/*   Updated: 2024/08/02 17:37:35 by fli              ###   ########.fr       */
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
	args->forks = NULL;
	pthread_mutex_init(&args->current_mutex, NULL);
	pthread_mutex_init(&args->armageddon_mutex, NULL);
	pthread_mutex_lock(&args->armageddon_mutex);
	args->armageddon = FALSE;
	pthread_mutex_unlock(&args->armageddon_mutex);
	pthread_mutex_init(&args->talking_stick, NULL);
}

suseconds_t	get_time_ms(void)
{
	struct timeval	tp;
	suseconds_t		current_time;

	gettimeofday(&tp, NULL);
	current_time = ((tp.tv_sec * 1000000) + tp.tv_usec) / 1000;
	return (current_time);
}

time_t	time_from_start(t_arg *args)
{
	suseconds_t	current_time;

	current_time = get_time_ms();
	return (current_time - args->start_time);
}

void	print_action(t_arg *args, int name, char *action)
{
	pthread_mutex_lock(&args->armageddon_mutex);
	if (args->armageddon == TRUE)
	{
		pthread_mutex_unlock(&args->armageddon_mutex);
		return ;
	}
	pthread_mutex_unlock(&args->armageddon_mutex);
	pthread_mutex_lock(&args->talking_stick);
	printf("%ld %d %s\n", time_from_start(args), name, action);
	pthread_mutex_unlock(&args->talking_stick);
}
