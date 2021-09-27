/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 16:31:30 by ogenser           #+#    #+#             */
/*   Updated: 2021/09/09 14:25:49 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_initc(t_mother *s)
{
	t_command	*c;

	c = (t_command *)ft_malloc(&c, sizeof(c) * 1000);
	c->line = NULL;
	c->command = "ls";
	c->retvalue = 0;
	c->nbarg = 0;
	c->arg = NULL;
	c->isfollowedbypipe = 0;
	c->nextpipe = 0;
	c->isprecededbypipe = 0;
	c->previouspipe = NULL;
	c->isinputfile = 0;
	c->outfile = NULL;
	c->isinputfile = 0;
	c->inputfile = 0;
	c->iserrofile = 0;
	c->errorfile = NULL;
	c->cmd_status = 0;
	s->c = c;
	// return(&c);
}

void    ft_lexinit(t_mother *s)
{
	t_lexer	*lex;
	t_token *tok;

	//regles d'init : si pas de valeurs speciales tt les pointeurs a NULL (y compris 
	//les char *) et les char a '\0' -> necessaire pour debug valgrind etc
	//declarer struct locale puis assigner sinon ca fout le bordel
	lex = malloc(sizeof(t_lexer));
	tok = malloc(sizeof(t_token));
	tok->token = NULL;
	tok->type = '\0';
	tok->prev = NULL;
	tok->next = NULL;
    lex->quote = 0;
	lex->token_nb = 0;
	lex->delimiter = NULL;
	lex->std_input_redir = NULL;
	s->lex = lex;
	s->lex->first_token = tok;
}

void	ft_structinit(t_mother *s)
{
	// s = ft_malloc(s, sizeof(s));

	// s = (t_mother *)ft_malloc(s, sizeof(s) * 100);
	s->line = NULL;
	s->nbcmd = 0;
	s->pipe = 0;
	s->exitret = 0;
	s->path = NULL;
	s->redirect_mem = 0;
	ft_initc(s);
	ft_lexinit(s);
}

void	ft_end(t_mother *s)
{
	if (s->line)
		free(s->line);
	// if (s->c)
	// 	free(s->c);
	ft_clear_history();
	exit(0);
}