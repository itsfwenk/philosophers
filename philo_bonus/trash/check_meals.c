/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_meals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 19:38:28 by fli               #+#    #+#             */
/*   Updated: 2024/08/01 22:19:40 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// void	*meal_count(void *args)
// {
// 	time_t	before;
// 	time_t	after;
// 	t_arg	*arg;
// 	int		current;

// 	current = arg->current;
// 	arg = (t_arg *)args;
// 	while (arg->meals[current] < arg->min_meals)
// 	{
// 		before = get_time_ms();
// 		sem_wait(arg->philos[current].eating_sem);
// 		after = get_time_ms();
// 		if (after - before > arg->eat_t)
// 		{
// 			sem_wait(arg->meals_sem);
// 			(arg->meals[current])++;
// 			sem_post(arg->meals_sem);
// 		}
// 	}
// }

// void	all_eat(t_arg *args)
// {
// 	int	i;
// 	int	*meal_tab;

// 	meal_tab = args->meals;
// 	while (TRUE)
// 	{
// 		i = 0;
// 		while (i < args->n_philo)
// 		{
// 			sem_wait(args->meals_sem);
// 			if (meal_tab[i] >= args->min_meals)
// 			{
// 				sem_post(args->meals_sem);
// 				i++;
// 			}
// 			else
// 			{
// 				sem_post(args->meals_sem);
// 				break ;
// 			}
// 		}
// 		if (i == args->n_philo)
// 			break ;
// 	}
// 	return ;
// }

// void	*all_eat_t(void *args)
// {
// 	t_arg	*arg;

// 	arg = (t_arg *)args;
// 	all_eat(arg);
// 	kill(arg->philos[0].pid, SIGTERM);
// 	sem_wait(arg->armageddon);
// 	arg->stop_dinner = TRUE;
// 	sem_post(arg->armageddon);
// }

// void	check_meals(t_arg *args, t_philo *philos)
// {
// 	int	i;
// 	int	meals[200];

// 	memset(meals, 0, 200 * sizeof(int));
// 	args->meals = meals;
// 	if (args->min_meals == -1)
// 		return ;
// 	i = 0;
// 	while (i < args->n_philo)
// 	{
// 		args->current = i;
// 		pthread_create(&(philos[i].check_meal_tid), NULL, meal_count, args);
// 		usleep(1000);
// 		i++;
// 	}
// 	pthread_create(&(args->all_eat), NULL, all_eat_t, args);
// 	return ;
// }
