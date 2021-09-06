/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 17:19:19 by ogenser           #+#    #+#             */
/*   Updated: 2021/07/07 18:21:33 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	ft_strlonglen(char *str, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (str[i] != '\0' && i < n)
		i++;
	return (i);
}

int	ft_strlcat(char *dest, char *src, unsigned int size)
{
	unsigned int	j;
	unsigned int	k;
	unsigned int	sizedest;

	j = 0;
	k = 0;
	sizedest = ft_strlonglen(dest, size);
	while (src[k])
	{
		k++;
	}
	if (size == 0)
		return (k);
	if (size == sizedest)
		return (k + size);
	while ((sizedest + j) < size - 1 && src[j])
	{
		dest[sizedest + j] = src[j];
		j++;
	}
	dest[sizedest + j] = '\0';
	return (sizedest + k);
}
