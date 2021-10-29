/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 16:31:30 by ogenser           #+#    #+#             */
/*   Updated: 2021/10/04 16:00:46 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_initc(t_mother *s)
{
	s->c = ft_malloc(&s->c, sizeof(t_command));
	s->c->line = NULL;
	s->c->command = NULL;
	s->c->retvalue = 0;
	s->c->nbarg = 0;
	s->c->arg = NULL;
	s->c->isfollowedbypipe = 0;
	s->c->isfollowedbyche = 0;
	s->c->isfollowedbydoubleche = 0;
	s->c->nextpipe = 0;
	s->c->isprecededbypipe = 0;
	s->c->isprecededbyche = 0;
	s->c->isprecededbydoubleche = 0;
	s->c->previouspipe = NULL;
	s->c->isinputfile = 0;
	s->c->outfile = NULL;
	s->c->isinputfile = 0;
	s->c->inputfile = 0;
	s->c->iserrofile = 0;
	s->c->errorfile = NULL;
	s->c->cmd_status = 0;
}

void	ft_lexinit(t_mother *s)
{
	t_lexer	*lex;
	t_token	*tok;

	lex = malloc(sizeof(t_lexer));
	tok = malloc(sizeof(t_token));
	tok->token = NULL;
	tok->type = '\0';
	tok->pre_space = 0;
	tok->prev = NULL;
	tok->next = NULL;
	lex->quote = 0;
	lex->token_nb = 0;
	lex->delimiter = NULL;
	lex->input_redir = NULL;
	s->lex = lex;
	s->lex->first_token = tok;
}

void	ft_structinit(t_mother *s)
{
	s->line = NULL;
	s->nbcmd = 0;
	s->pipe = 0;
	s->exitret = 0;
	s->redirect_mem = 0;
	ft_initc(s);
	ft_lexinit(s);
}

void	ft_end(t_mother *s)
{
	free_t_token(s);
	free_t_cmd(s);
	ft_clear_history();
}

void	free_t_mother(t_mother *s)
{
	free(s->path);
	ft_free_array(s->env);
}
