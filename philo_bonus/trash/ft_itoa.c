/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 21:16:27 by fli               #+#    #+#             */
/*   Updated: 2024/08/01 21:16:53 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_itoalen(int n)
{
	int	i;
	int	nbis;

	i = 1;
	nbis = n;
	while (nbis / 10 != 0)
	{
		nbis = nbis / 10;
		i++;
	}
	if (n < 0)
		return (i + 1);
	else
		return (i);
}

char	*ft_itoa(int n)
{
	int			i;
	long int	nbr;
	char		*itoa;

	nbr = n;
	itoa = malloc((ft_itoalen(n)) + sizeof(char));
	if (itoa == NULL)
		return (NULL);
	i = ft_itoalen(n);
	if (n == 0)
		itoa[0] = '0';
	if (nbr < 0)
	{
		nbr = nbr * (-1);
		itoa[0] = '-';
	}
	itoa[i] = '\0';
	while (nbr != 0 && itoa[i] != '-')
	{
		i--;
		itoa[i] = (nbr % 10) + 48;
		nbr = nbr / 10;
	}
	return (itoa);
}