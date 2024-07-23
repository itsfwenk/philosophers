/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:17:52 by fli               #+#    #+#             */
/*   Updated: 2024/07/23 18:26:28 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <pthread.h>

# ifndef TRUE
#  define TRUE 1

# endif

# ifndef FALSE
#  define FALSE 0

# endif

typedef struct s_arg
{
	int				n_philo;
	int				die_t;
	int				eat_t;
	int				sleep_t;
	pthread_t		*restrict thread;
	pthread_attr_t	*restrict attr;
	struct s_arg	*next;
}	t_arg;


/////////////////////// PHILO ///////////////////////


/////////////////////// PHILO_UTILS ///////////////////////

int	ft_atoi(char *s);

#endif
