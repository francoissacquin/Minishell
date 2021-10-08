/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 17:22:59 by ogenser           #+#    #+#             */
/*   Updated: 2021/09/08 11:03:32 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int ft_export(t_mother *s, t_command *cmd)
{
	int 	ret;
	int		i;
	int		j;
	char	*temp;
	t_token	temp_tok;

	ret = 0;
	// printf("%s\n", cmd->line);
	// printf("%zu\n",ft_strlen_array(cmd->arg));
	if (ft_strlen_array(cmd->arg) == 1)
	{
		i = 0;
		while (s->env[i] != NULL)
		{
			printf("declare -x ");
			j = 0;
			while(s->env[i][j] != '=')
			{
				printf("%c",s->env[i][j]);
				j++;
			}
			temp = ft_substr(s->env[i], 0, j);
			printf("=\"%s\"\n", getenv(temp));
			free(temp);
			i++;
		}
	}
	else
	{
		i = 1;
		while (cmd->arg[i] != 0)
		{
			temp_tok.token = cmd->arg[i];
			ft_type_env(&temp_tok);
			if (temp_tok.type == 'E')
				create_env(s, cmd->arg[i]);
			else if (ft_word_is_exportable(cmd->arg[i]))
				ret = 0;
			else
				ret = 1;
			i++;
		}
	}
	return(ret);
}

int		ft_word_is_exportable(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!(ft_isalnum(str[i])))
		{
			if (str[i] != '_')
				return (0);
		}
		i++;
	}
	return (1);
}