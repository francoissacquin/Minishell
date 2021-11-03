/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_types.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 20:19:55 by ogenser           #+#    #+#             */
/*   Updated: 2021/11/03 20:19:56 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	assign_types(t_mother *s)
{
	t_token	*temp;

	temp = s->lex->first_token;
	while (temp != NULL)
	{
		if (temp->type == 'S')
			write(2, "Error, input should not contain a separator\';\'\n", 47);
		if (temp->type == '\0' && temp->token != NULL)
			assign_type_conveyor_belt(s, temp);
		if (temp->type == 'e' && temp->token[1] == '?')
			ft_env_tok_overflow(temp, 2);
		if (temp->type == 'o')
			ft_type_pipe(temp);
		if (temp->type == '\0')
			temp->type = 'w';
		if (temp->type == 'q' || temp->type == 'e')
			expanding_env(s, temp);
		temp = temp->next;
	}
}

void	assign_type_conveyor_belt(t_mother *s, t_token *temp)
{
	ft_type_flag(temp);
	ft_type_env(temp);
	ft_type_path(s, temp);
	ft_type_cmd(s, temp);
	ft_type_built(temp);
	ft_type_op(temp);
}

//Using POSIX standards on shells section of IEEE Std 1003.1-2008 
// IEEE POSIX P1003.2/ISO 9945.2 Shell and Tools standard
void	ft_type_env(t_token *tok)
{
	int		i;

	i = 1;
	if (tok->token[0] == '$')
	{
		while (tok->token[i] && tok->token[i] != '=')
		{
			if (!(ft_isalnum(tok->token[i]) || tok->token[i] == '_'))
				return ;
			i++;
		}
		if (tok->token[i] == '\0')
			tok->type = 'e';
	}
	else
	{
		i = 0;
		ft_check_env_value(tok, &i);
	}
}

void	ft_type_built(t_token *tok)
{
	if (!(ft_strcmp(tok->token, "echo")))
		tok->type = 'b';
	else if (!(ft_strcmp(tok->token, "cd")))
		tok->type = 'b';
	else if (!(ft_strcmp(tok->token, "pwd")))
		tok->type = 'b';
	else if (!(ft_strcmp(tok->token, "export")))
		tok->type = 'b';
	else if (!(ft_strcmp(tok->token, "unset")))
		tok->type = 'b';
	else if (!(ft_strcmp(tok->token, "env")))
		tok->type = 'b';
	else if (!(ft_strcmp(tok->token, "exit")))
		tok->type = 'b';
	else
		return ;
}

void	ft_type_cmd(t_mother *s, t_token *tok)
{
	char	**array;
	int		i;
	int		exist;
	char	*temp;

	temp = ft_return_env_value(s, "PATH", 1);
	array = ft_split(temp, ':');
	free(temp);
	i = -1;
	if (ft_type_abs_cmd(tok) == 1)
	{
		ft_free_array(array);
		return ;
	}
	while (array[++i] != NULL)
	{
		exist = ft_stat_check(array[i], tok);
		if (exist == 0)
		{
			tok->type = 'c';
			ft_free_array(array);
			return ;
		}
	}
	ft_free_array(array);
}
