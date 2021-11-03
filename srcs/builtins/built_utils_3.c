/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 20:22:20 by ogenser           #+#    #+#             */
/*   Updated: 2021/11/03 20:22:21 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_sort_env(t_mother *s)
{
	int		len;
	int		i;

	len = ft_strlen_array(s->env);
	s->env_exp = ft_malloc(&s->env_exp, (len + 1) * sizeof(char *));
	i = 0;
	while (s->env[i])
	{
		s->env_exp[i] = strdup(s->env[i]);
		i++;
	}
	s->env_exp[i] = NULL;
	ft_bubble_sort(s, len);
}

void	ft_bubble_sort(t_mother *s, int len)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < len)
	{
		j = 0;
		while (j < len - 1 - i)
		{
			if (ft_strcmp(s->env_exp[j], s->env_exp[j + 1]) > 0)
			{
				temp = ft_strdup(s->env_exp[j]);
				free(s->env_exp[j]);
				s->env_exp[j] = ft_strdup(s->env_exp[j + 1]);
				free(s->env_exp[j + 1]);
				s->env_exp[j + 1] = ft_strdup(temp);
				free(temp);
			}
			j++;
		}
		i++;
	}
}

int	ft_updatepwd(t_mother *s, char *new_path, char *old_path)
{
	char	*temp;

	temp = ft_strjoin("PWD=", new_path);
	create_env(s, temp);
	free(temp);
	temp = ft_strjoin("OLDPWD=", old_path);
	create_env(s, temp);
	free(temp);
	return (0);
}
