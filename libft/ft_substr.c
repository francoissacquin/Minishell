/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 14:12:12 by ogenser           #+#    #+#             */
/*   Updated: 2021/07/07 18:30:38 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		i;
	char	*dest;

	i = 0;
	dest = NULL;
	dest = (char *)ft_malloc(dest, (len + 1));
	if (!s || dest == NULL)
		return (NULL);
	if (start < ft_strlen((char *)s))
	{
		while (s[start + i] && len--)
		{
			dest[i] = s[start + i];
			i++;
		}
	}
	dest[i] = 0;
	return (dest);
}
