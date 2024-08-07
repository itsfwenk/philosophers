/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 18:12:15 by fli               #+#    #+#             */
/*   Updated: 2024/08/06 15:04:19 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_arg_wrap(int ac, char **av)
{
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

static int	arg_isdigit(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j] != '\0')
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (FALSE);
			j++;
		}
		i++;
	}
	return (TRUE);
}

int	check_arg(int ac, char **av)
{
	if (ac != 5 && ac != 6)
	{
		printf("Wrong number of arguments...\n");
		return (FALSE);
	}
	if (arg_isdigit(ac, av) == FALSE)
	{
		printf("Arguments must be digits...\n");
		return (FALSE);
	}
	if (ft_atoi(av[1]) < 1 || ft_atoi(av[1]) > 200)
	{
		printf("Wrong number of philosophers...\n");
		return (FALSE);
	}
	if (check_arg_wrap(ac, av) == FALSE)
		return (FALSE);
	return (TRUE);
}
