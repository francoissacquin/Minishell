/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 17:24:02 by fsacquin          #+#    #+#             */
/*   Updated: 2021/09/06 15:51:14 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

int		ft_env_cmp(char *env1, char *var)
{
	int		i;

	i = 0;
	while (env1[i] && var[i])
	{
		if (env1[i] != var[i])
			return (0);
		else if (env1[i] == '=' && var[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int		ft_env_cmp_arg(char *env1, char *var)
{
	int		i;

	i = 0;
	while (env1[i] && var[i])
	{
		if (env1[i] != var[i])
			return (0);
		i++;
	}
	if (env1[i] == '=')
			return (1);
	return (0);
}

// type = 1 for arg search, type = 2 for a arg=value char search
char	*ft_return_env_value(t_mother *s, char *var, int type)
{
	int		i;
	int		index;

	i = 0;
	index = 0;
	while (s->env[i] != NULL)
	{
		if (type == 1)
		{
			index = ft_env_cmp_arg(s->env[i], var);
			if (index != 0)
				return (ft_substr(s->env[i], index, ft_strlen(s->env[i]) - index));
		}
		else if (type == 2)
		{
			index = ft_env_cmp(s->env[i], var);
			if (index != 0)
				return(ft_substr(s->env[i], index, ft_strlen(s->env[i]) - index));
		}
		i++;
	}
	return (NULL);
}
