/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_checking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 20:18:55 by ogenser           #+#    #+#             */
/*   Updated: 2021/11/03 20:18:56 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	pre_exec_arg_checking(t_mother *s, t_command *cmd, t_token *tok)
{
	(void)s;
	if (cmd->command == NULL)
		return ;
	if (!(ft_strcmp("echo", cmd->command)) && tok->type == 'f')
		return ;
	else if (cmd->cmd_status == 1)
	{
		if (!(ft_strcmp(cmd->command, "env")) && cmd->nbarg == 1)
			write(2, "error, env takes no flag or argument\n", 37);
	}
}

void	check_echo_flag(t_mother *s, t_token *tok)
{
	int		i;

	(void)s;
	i = 1;
	if (tok->token[0] != '-')
		return ;
	if (tok->next != NULL && ft_strchr("qwp", tok->next->type)
		&& tok->next->pre_space == 0)
	{
		check_echo_flag_plus(s, tok);
	}
	while (tok->token[i])
	{
		if (tok->token[i] != 'n')
		{
			tok->type = 'w';
			return ;
		}
		i++;
	}
	if (i > 2)
	{
		free(tok->token);
		tok->token = ft_strdup("-n");
	}
}

void	check_echo_flag_plus(t_mother *s, t_token *tok)
{
	char	*temp;

	(void)s;
	temp = ft_strdup(tok->next->token);
	tok->token = ft_strjoin_env(tok->token, temp);
	free(temp);
	free(tok->next->token);
	if (tok->next->next != NULL && tok->next->next->pre_space == 1)
	{
		tok->next->token = ft_strdup("");
		temp = ft_strdup(tok->token);
		free(tok->token);
		tok->token = ft_strjoin(temp, " ");
		free(temp);
	}
	else
		tok->next->token = ft_strdup("");
	tok->next->type = 'q';
}
