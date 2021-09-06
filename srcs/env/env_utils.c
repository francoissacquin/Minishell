/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsacquin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 17:24:02 by fsacquin          #+#    #+#             */
/*   Updated: 2021/09/02 17:24:04 by fsacquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../inc/minishell.h"

size_t	ft_strlen_array(char **array)
{
	size_t	i;

	i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
}

void	ft_free_array(char **array)
{
	int		len;

	len = ft_strlen_array(array);
	while (len > 0)
	{
		free(array[len - 1]);
		len--;
	}
	free(array);
}

int		ft_env_cmp(char *env1, char *str)
{
	int		result;
	int		i;

	i = 0;
	while (env[i] && str[i])
	{
		if (env[i] != str[i])
			return (0);
		else
			i++;

	}
	if (env[i] == ' ' && env[i + 1] == ':')
			return (1);
	else
		return (0);
}
