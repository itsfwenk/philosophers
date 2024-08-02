/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:30:32 by fli               #+#    #+#             */
/*   Updated: 2024/08/02 18:16:10 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	optimal_frequency(t_arg *args)
{
	int	min_cycle_time;
	int	max_wait_time;
	int	check_frequency;
	int	optimal_check_frequency;

	min_cycle_time = args->eat_t + args->sleep_t;
	max_wait_time = min_cycle_time + (args->eat_t - 1);
	check_frequency = max_wait_time / 2;
	if (check_frequency < args->die_t / 2)
		optimal_check_frequency = check_frequency;
	else
		optimal_check_frequency = (args->die_t / 2);
	return (optimal_check_frequency);
}

static int	check_arg_wrap(int ac, char **av)
{
	if (ft_atoi(av[4]) < 60 || ft_atoi(av[4]) == INT_MAX)
	{
		printf("Wrong time input for Time to Sleep...\n");
		return (FALSE);
	}
	if (ac == 6)
	{
		if (ft_atoi(av[5]) < 0 || ft_atoi(av[5]) == INT_MAX)
		{
			printf("Wrong time input for Minimal Meals...\n");
			return (FALSE);
		}
	}
	return (TRUE);
}

int	check_arg(int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (FALSE);
	if (ft_atoi(av[1]) < 1 || ft_atoi(av[1]) > 200)
	{
		printf("Wrong number of philosophers...\n");
		return (FALSE);
	}
	if (ft_atoi(av[2]) < 60 || ft_atoi(av[2]) == INT_MAX)
	{
		printf("Wrong time input for Time to Die...\n");
		return (FALSE);
	}
	if (ft_atoi(av[3]) < 60 || ft_atoi(av[3]) == INT_MAX)
	{
		printf("Wrong time input for Time to Eat...\n");
		return (FALSE);
	}
	if (check_arg_wrap(ac, av) == FALSE)
		return (FALSE);
	return (TRUE);
}
