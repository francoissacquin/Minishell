/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 19:30:40 by ogenser           #+#    #+#             */
/*   Updated: 2020/04/14 19:30:46 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const char	*bsrc;
	char		*bdest;

	if (!src && !dest)
		return (0);
	bdest = dest;
	bsrc = src;
	while (n > 0)
	{
		*bdest++ = *bsrc++;
		n--;
	}
	return (dest);
}
