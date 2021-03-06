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

int	ft_export(t_mother *s, t_command *cmd)
{
	int		ret;
	int		i;

	ret = 0;
	if (ft_strlen_array(cmd->arg) == 1)
	{
		i = 0;
		ft_sort_env(s);
		while (s->env[i] != NULL)
			ft_export_no_arg(s, &i);
		ft_free_array(s->env_exp);
	}
	else
	{
		i = 1;
		while (cmd->arg[i] != NULL)
			ft_export_with_arg(s, cmd, &i, &ret);
	}
	return (ret);
}

void	ft_export_with_arg(t_mother *s, t_command *cmd, int *i, int *ret)
{
	t_token	temp_tok;

	temp_tok.token = cmd->arg[*i];
	ft_type_env(&temp_tok);
	if (temp_tok.type == 'E')
		create_env(s, cmd->arg[*i]);
	else if (cmd->arg[*i][0] == '-')
		*ret = 2;
	else if (ft_word_is_exportable(cmd->arg[*i]))
		*ret = 0;
	else
		*ret = 1;
	*i = *i + 1;
}

void	ft_export_no_arg(t_mother *s, int *i)
{
	char	*temp;
	char	*value;
	int		j;

	write(1, "declare -x ", 11);
	j = 0;
	while (s->env_exp[*i][j] != '=')
		j++;
	temp = ft_substr(s->env_exp[*i], 0, j);
	write(1, temp, ft_strlen(temp));
	write(1, "=\"", 2);
	value = ft_return_env_value(s, temp, 1);
	write(1, value, ft_strlen(value));
	write(1, "\"\n", 2);
	free(temp);
	free(value);
	*i = *i + 1;
}

int	ft_word_is_exportable(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (i == 0 && (ft_isdigit(str[i]) || str[i] == '='))
			return (0);
		if (!(ft_isalnum(str[i])))
		{
			if (!(ft_strchr("_\\", str[i])))
				return (0);
		}
		i++;
	}
	if (i == 0)
		return (0);
	return (1);
}
