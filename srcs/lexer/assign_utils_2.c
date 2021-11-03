/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 20:20:00 by ogenser           #+#    #+#             */
/*   Updated: 2021/11/03 20:20:02 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_type_flag(t_token *tok)
{
	int		i;

	i = 1;
	if (tok->token[0] == '-')
	{
		while (tok->token[i])
		{
			if (!(ft_isalpha(tok->token[i])))
				return ;
			i++;
		}
		tok->type = 'f';
	}
}

void	ft_type_op(t_token *tok)
{
	if (!(ft_strcmp(tok->token, "<")))
		tok->type = 'o';
	else if (!(ft_strcmp(tok->token, "<<")))
		tok->type = 'o';
	else if (!(ft_strcmp(tok->token, ">")))
		tok->type = 'o';
	else if (!(ft_strcmp(tok->token, ">>")))
		tok->type = 'o';
	else if (ft_is_op_redir(tok->token))
		tok->type = 'o';
}

void	ft_type_pipe(t_token *tok)
{
	if (!(ft_strcmp(tok->token, "|")))
		tok->type = 'P';
}

void	ft_env_tok_overflow(t_token *tok, int limiter)
{
	t_token	*new;
	char	*temp;
	char	*temp2;

	temp = ft_substr(tok->token, limiter, ft_strlen(tok->token) - 2);
	if (tok->next != NULL)
	{
		temp2 = ft_strdup(tok->next->token);
		free(tok->next->token);
		tok->next->token = ft_strjoin(temp, temp2);
		tok->next->pre_space = 0;
		free(temp);
		free(temp2);
	}
	else
	{
		new = ft_malloc(&new, sizeof(t_token));
		new->token = temp;
		new->type = '\0';
		new->pre_space = 0;
		new->prev = tok;
		new->next = NULL;
		tok->next = new;
	}
	finish_env_tok_over(tok);
}

void	finish_env_tok_over(t_token *tok)
{
	char	*temp;

	temp = ft_substr(tok->token, 0, 2);
	free(tok->token);
	tok->token = temp;
}
