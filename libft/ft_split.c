/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 15:28:08 by ogenser           #+#    #+#             */
/*   Updated: 2021/07/07 18:25:56 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

char	*filler(char const *s, char c)
{
	int		i;
	char	*array;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	array = NULL;
	array = (char *)ft_malloc(array, (sizeof(char) * (i + 1)));
	if (array == NULL)
		return (NULL);
	i = 0;
	while (s[i] != c && s[i])
	{
		array[i] = s[i];
		i++;
	}
	array[i] = '\0';
	return (array);
}

int	dirsize(char const *s, char c)
{
	int	j;

	j = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s != c && *s)
		{
			j++;
			while (*s != c && *s)
				s++;
		}
	}
	return (j + 1);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**dir;

	i = 0;
	dir = NULL;
	dir = (char **)ft_malloc(dir, (dirsize(s, c) * sizeof(char *)));
	if (dir == NULL)
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s != c && *s)
		{
			dir[i] = filler(s, c);
			i++;
			while (*s && *s != c)
				s++;
		}
	}
	dir[i] = NULL;
	return (dir);
}
