/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 17:18:27 by ogenser           #+#    #+#             */
/*   Updated: 2021/07/08 19:01:28 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		j;

	j = ft_strlen((char *)s);
	while (j >= 0)
	{
		if (s[j] == (char)c)
			return ((char *)&s[j]);
		j--;
	}
	return (NULL);
}
