/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 21:12:33 by fli               #+#    #+#             */
/*   Updated: 2024/08/01 21:17:52 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

static size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	cp;

	i = 0;
	if (size == 0 || !src)
		return (ft_strlen(src));
	if (ft_strlen(src) < size)
		cp = ft_strlen(src);
	else
		cp = size - 1;
	while (i < cp && src)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

static size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dstinit;

	i = 0;
	dstinit = ft_strlen(dst);
	if (size <= dstinit)
		return (size + ft_strlen(src));
	else
	{
		while (i < size - dstinit - 1 && src[i] != '\0')
		{
			dst[dstinit + i] = src[i];
			i++;
		}
		dst[dstinit + i] = '\0';
	}
	return (dstinit + ft_strlen(src));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		tot;
	char	*joined;

	tot = ft_strlen(s1) + ft_strlen(s2) + 1;
	joined = malloc((tot) * sizeof(char));
	if (joined == NULL)
		return (NULL);
	ft_strlcpy(joined, s1, ft_strlen(s1) + 1);
	ft_strlcat(joined, s2, tot);
	return (joined);
}