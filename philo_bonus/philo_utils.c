/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:47:21 by fli               #+#    #+#             */
/*   Updated: 2024/08/02 00:07:57 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

time_t	get_time_ms(void)
{
	struct timeval	tp;
	time_t			current_time;

	gettimeofday(&tp, NULL);
	// printf("sec time %ld\n", tp.tv_sec);
	// printf("usec time %ld\n", tp.tv_usec);
	current_time = ((tp.tv_sec * 1000000) + tp.tv_usec) / 1000;
	return (current_time);
}

time_t	time_from_start(t_arg *args)
{
	time_t	current_time;

	current_time = get_time_ms();
	// printf("current time %ld\n", current_time);
	// printf("start time %ld\n", ags->start_time);
	return (current_time - args->start_time);
}

void	print_action(t_arg *args, int name, char *action)
{
	sem_wait(args->armageddon);
	if (args->stop_dinner == TRUE)
	{
		sem_post(args->armageddon);
		return ;
	}
	sem_post(args->armageddon);
	sem_wait(args->talking_stick);
	printf("%ld %d %s\n", time_from_start(args), name, action);
	// printf("its %d\n", name);
	sem_post(args->talking_stick);
}