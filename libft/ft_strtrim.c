/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 17:14:40 by ogenser           #+#    #+#             */
/*   Updated: 2021/07/07 18:17:41 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	ft_is_in_set(char c, char const *charset)
{
	unsigned int	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	debut;
	size_t	fin;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	debut = 0;
	while (s1[debut] && ft_is_in_set(s1[debut], set))
		debut++;
	fin = ft_strlen((char *)s1) - 1;
	if (debut == fin)
		len = 0;
	else
	{
		while (fin >= debut && ft_is_in_set(s1[fin], set))
			fin--;
		len = fin - debut + 1;
	}
	return (ft_substr(s1, debut, len));
}
