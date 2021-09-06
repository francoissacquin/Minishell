/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 22:22:00 by ogenser           #+#    #+#             */
/*   Updated: 2021/07/07 18:23:07 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*str;

	str = NULL;
	str = (void *)ft_malloc(str, (size * count));
	if (str == NULL)
		return (NULL);
	ft_memset(str, 0, size * count);
	return ((void *)str);
}
