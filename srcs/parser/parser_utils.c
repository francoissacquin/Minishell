/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 20:19:19 by ogenser           #+#    #+#             */
/*   Updated: 2021/11/03 20:19:20 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_cmd_blt(t_mother *s, t_token *tok, int *i)
{
	t_command	*last;

	last = ft_last_cmd(s->c);
	if (s->redirect_mem == 5 && tok->next != NULL)
		ft_redir_5(s, tok, i, last);
	else if (tok->prev != NULL && last->line != NULL)
	{
		if (tok->prev->type == 'P')
			fill_next_command(s, last, tok, i);
		else if (s->redirect_mem == 5)
			plug_redir_5(s, last);
		else if (s->redirect_mem == 2)
			ft_redir_in(s, tok, last);
		else if (s->redirect_mem == 3 || s->redirect_mem == 4)
			ft_redir_out(s, tok, last);
		else
		{
			tok->type = 'w';
			ft_add_args(s, tok);
		}
	}
	else
		fill_first_command(s, tok);
}

void	ft_redir_in(t_mother *s, t_token *tok, t_command *last)
{
	last->isinputfile = 1;
	if (last->inputfile != NULL)
	{
		free(last->inputfile);
		last->isprecededbydoubleche = 0;
	}
	last->inputfile = ft_strdup(tok->token);
	last->isprecededbyche = 1;
	s->redirect_mem = 0;
}

void	ft_redir_5(t_mother *s, t_token *tok, int *i, t_command *last)
{
	if (tok->next != NULL && ft_strchr("bc", tok->next->type)
		&& s->nbcmd == 0)
	{
		fill_first_command(s, tok->next);
		plug_redir_5(s, s->c);
	}
	else if (tok->next != NULL && ft_strchr("bc", tok->next->type)
		&& s->nbcmd > 0)
	{
		fill_next_command(s, last, tok->next, i);
		last = ft_last_cmd(s->c);
		plug_redir_5(s, last);
	}
	else
	{
		if (last->inputfile == NULL)
			plug_redir_5(s, last);
		s->redirect_mem = 0;
	}
}

void	ft_redir_out(t_mother *s, t_token *tok, t_command *last)
{
	int		fd;

	last->isoutfile = 1;
	fd = open(tok->token, O_CREAT | O_RDWR | O_APPEND, 0666);
	close(fd);
	if (last->outfile != NULL)
	{
		free (last->outfile);
		last->outfile = NULL;
	}
	last->outfile = ft_strdup(tok->token);
	if (s->redirect_mem == 3)
	{
		last->isfollowedbydoubleche = 0;
		last->isfollowedbyche = 1;
	}
	else if (s->redirect_mem == 4)
	{
		last->isfollowedbyche = 0;
		last->isfollowedbydoubleche = 1;
	}
	s->redirect_mem = 0;
}

void	plug_redir_5(t_mother *s, t_command *last)
{
	char			*temp;
	int				fd;
	struct stat		s_buf;

	if (last->inputfile != NULL)
		free(last->inputfile);
	last->isprecededbyche = 0;
	if (stat("./redir_input.txt", &s_buf) == 0)
		unlink("redir_input.txt");
	fd = open("redir_input.txt", O_CREAT | O_RDWR | O_APPEND, 0666);
	if (fd < 0)
		s->ret = 1;
	write(fd, s->lex->input_redir, ft_strlen(s->lex->input_redir));
	close(fd);
	last->isinputfile = 1;
	temp = getenv("PWD");
	last->inputfile = ft_strdup("redir_input.txt");
	last->isprecededbydoubleche = 1;
}
