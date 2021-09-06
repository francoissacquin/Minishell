/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 13:45:02 by ogenser           #+#    #+#             */
/*   Updated: 2021/07/07 18:07:15 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

char	*ft_strdup(char *src)
{
	char	*tab;
	int		i;

	i = 0;
	tab = NULL;
	tab = ft_malloc(tab, (sizeof(*src) * ft_strlen(src) + 1));
	if (tab == NULL)
		return (NULL);
	while (src[i])
	{
		tab[i] = src[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}
