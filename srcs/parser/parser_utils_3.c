/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 20:19:29 by ogenser           #+#    #+#             */
/*   Updated: 2021/11/03 20:19:30 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	fill_next_command(t_mother *s, t_command *last, t_token *tok, int *i)
{
	t_command	*next;

	last->isfollowedbypipe = 1;
	add_cmd_elem(s, tok, i);
	next = ft_last_cmd(s->c);
	last->nextpipe = next;
	next->previouspipe = last;
	next->nextpipe = NULL;
	next->isprecededbypipe = 1;
	next->isprecededbyche = 0;
	next->isprecededbydoubleche = 0;
	next->isfollowedbypipe = 0;
	next->isfollowedbyche = 0;
	next->isfollowedbydoubleche = 0;
	next->isinputfile = 0;
	next->inputfile = NULL;
	next->isoutfile = 0;
	next->outfile = NULL;
	s->pipe++;
}

void	fill_first_command(t_mother *s, t_token *tok)
{
	s->c->command = ft_strdup(tok->token);
	s->c->line = ft_strdup(tok->token);
	s->c->retvalue = 0;
	s->c->nbarg = 1;
	s->c->arg = ft_malloc(&s->c->arg, sizeof(char *) * 2);
	s->c->arg[0] = ft_strdup(tok->token);
	s->c->arg[1] = NULL;
	if (tok->type == 67)
		s->c->cmd_status = 3;
	else
		s->c->cmd_status = tok->type - 97;
	s->nbcmd++;
}

int	ft_add_operator(t_mother *s, t_token *tok, int *i)
{
	t_command	*last;

	last = ft_last_cmd(s->c);
	if (tok->type == 'P')
		return (ft_add_sub_operator(s, tok, last));
	else if (tok->type == 'o')
	{
		if (tok->next != NULL)
		{
			if (ft_strchr("bcwep", tok->next->type))
				assign_redirect(s, tok, i);
			else
			{
				write(2, "Error, operator cannot take this argument\n", 42);
				s->ret = 1;
				return (1);
			}
		}
		if (tok->prev != NULL)
		{
			if (last->line != NULL && ft_strrchr("bcwefpq", tok->prev->type))
				assign_redirect(s, tok, i);
		}
	}
	return (0);
}

int	ft_add_sub_operator(t_mother *s, t_token *tok, t_command *last)
{
	if (last->line == NULL || last->command == NULL || last->arg == NULL)
	{
		write(2, "wrong pipe here, last command does not exist\n", 45);
		s->ret = 1;
		return (1);
	}
	if (tok->next != NULL)
	{
		if (ft_strchr("bc", tok->next->type))
			return (0);
		else
		{
			write(2, "pipe leads to non valid command\n", 32);
			s->ret = 1;
			return (1);
		}
	}
	else
	{
		write(2, "pipe is last token???\n", 22);
		s->ret = 1;
		return (1);
	}
	return (0);
}

int	ft_strnstr_index(char *haystack, char *needle, int len)
{
	int		i;
	int		j;

	i = 0;
	if (!needle || needle[i] == '\0')
		return (-1);
	while (haystack[i])
	{
		j = 0;
		while (i + j < len && needle[j] == haystack[i + j])
		{
			if (needle[j + 1] == '\0')
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}
