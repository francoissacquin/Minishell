/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 20:42:45 by ogenser           #+#    #+#             */
/*   Updated: 2021/07/07 18:24:15 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*exceptions(int n)
{
	char	*str;

	if (n == 0)
	{
		str = NULL;
		str = ft_malloc(str, 2);
		if (str == NULL)
			return (NULL);
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	str = NULL;
	str = ft_malloc(str, 2);
	if (str == NULL)
		return (NULL);
	return (str);
}

char	*compte(unsigned int n, int taille, int signe)
{
	char	*str;

	str = NULL;
	str = (char *)ft_malloc(str, (sizeof(*str) * (taille + 1)));
	if (str == NULL)
		return (NULL);
	str[taille] = '\0';
	taille--;
	while (n > 0)
	{
		str[taille] = (n % 10) + '0';
		taille--;
		n /= 10;
	}
	if (signe == 1)
		str[taille] = '-';
	return (str);
}

int	get_taille(int n)
{
	int	taille;

	taille = 0;
	if (n < 0)
	{
		taille++;
	}
	while (n != 0)
	{
		n /= 10;
		taille++;
	}
	return (taille);
}

char	*ft_itoa(int n)
{
	char			*str;
	unsigned int	nb;
	int				taille;
	int				signe;

	taille = get_taille(n);
	signe = 0;
	if (n == 0)
		return (&*exceptions(n));
	if (n < 0)
	{
		nb = (unsigned int)(n * -1);
		signe++;
	}
	else
		nb = (unsigned int)n;
	str = compte(nb, taille, signe);
	if (!n)
		*str = '0';
	return (str);
}
