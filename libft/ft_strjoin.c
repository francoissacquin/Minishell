/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 20:40:48 by ogenser           #+#    #+#             */
/*   Updated: 2021/07/07 18:27:55 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	int		taille;
	int		i;

	i = 0;
	taille = ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1;
	dest = NULL;
	dest = (char *)ft_malloc(dest, (sizeof(char) * taille));
	if (dest == NULL)
		return (NULL);
	while (*s1 && i < taille)
	{
		dest[i] = *s1;
		s1++;
		i++;
	}
	while (*s2 && i < taille)
	{
		dest[i] = *s2;
		s2++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
