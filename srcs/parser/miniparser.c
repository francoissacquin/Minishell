#include "../../inc/minishell.h"

void	miniparser(t_mother *s)
{
	t_token	*tok;
	int		i;

	tok = s->lex->first_token;
	i = 0;
	while(tok->next != NULL)
	{
		ft_tok_conveyor_belt(s, tok, &i);
		tok = tok->next;
		i++;
	}
	if (tok->token != NULL)
		ft_tok_conveyor_belt(s, tok, &i);
}

void	ft_tok_conveyor_belt(t_mother *s, t_token *tok, int *i)
{
	if (i == 0 && ft_strchr("pPf", tok->type))
		ft_wrong_input(s, tok, i);
	else if (ft_strchr("cb", tok->type))
		ft_cmd_blt(s, tok, i);
	else if (ft_strchr("Po", tok->type))
		ft_add_operator(s, tok, i);
	else if (ft_strchr("wpfd", tok->type) && s->redirect_mem == 0)
		ft_add_args(s, tok, i);
	else if (ft_strchr("wp", tok->type) && s->redirect_mem != 0)
		ft_cmd_blt(s, tok, i);
	else if (ft_strchr("eq", tok->type))
	{
		expanding_env(s, tok);
		ft_add_args(s, tok, i);
	}
}

void	ft_cmd_blt(t_mother *s, t_token *tok, int *i)
{
	t_command	*last;
	t_command	*next;

	last = ft_last_cmd(s->c);
	//printf("pour passage %i on a s->redir = %i\n", *i, s->redirect_mem);
	if (tok->prev != NULL && last->line != NULL)
	{
		if (tok->prev->type == 'P')
		{
			//printf("--creation post pipe avec s->redir = %i\n", s->redirect_mem);
			last->isfollowedbypipe = 1;
			add_cmd_elem(s, tok, i);
			next = ft_last_cmd(s->c);
			last->nextpipe = next;
			next->previouspipe = last;
			next->nextpipe = NULL;
			next->isprecededbypipe = 1;
			next->isfollowedbypipe = 0;
			next->isinputfile = 0;
			next->inputfile = NULL;
			next->isoutfile = 0;
			next->outfile = NULL;
			s->pipe++;
		}
		else if (s->redirect_mem == 5)
		{
			last->nbarg++;
			ft_add_arg_array(last, s->lex->std_input_redir);
			if (last->line == NULL)
				last->line = ft_strdup(s->lex->std_input_redir);
			else
				last->line = ft_strjoin(last->line, ft_strjoin(" ", s->lex->std_input_redir));
			last->isprecededbypipe = 3;
			s->redirect_mem = 0;
		}
		else if (s->redirect_mem == 2)
		{
			last->isinputfile = 1;
			last->inputfile = ft_strdup(tok->token);
			last->isprecededbypipe = 2;
			s->redirect_mem = 0;
		}
		else if (s->redirect_mem == 3 || s->redirect_mem == 4)
		{
			last->isoutfile = 1;
			last->outfile = ft_strdup(tok->token);
			if (s->redirect_mem == 3)
				last->isfollowedbypipe = 2;
			else if (s->redirect_mem == 4)
				last->isfollowedbypipe = 3;
			s->redirect_mem = 0;
		}
		else
		{
			tok->type = 'w';
			ft_add_args(s, tok, i);
		}
	}
	else
	{
		//printf("--creation premier element avec s->redir = %i\n", s->redirect_mem);
		s->c->command = ft_strdup(tok->token);
		s->c->line = ft_strdup(tok->token);
		s->c->retvalue = 0;
		s->c->nbarg = 1;
		s->c->arg = ft_malloc(&s->c->arg, sizeof(char *) * 2);
		s->c->arg[0] = ft_strdup(tok->token);
		s->c->arg[1] = NULL;
		s->c->cmd_status = tok->type - 97;
		s->nbcmd++;
		s->c->isfollowedbypipe = 0;
		s->c->nextpipe = NULL;
		s->c->isprecededbypipe = 0;
		s->c->previouspipe = NULL;
		s->c->isinputfile = 0;
		s->c->inputfile = NULL;
		s->c->isoutfile = 0;
		s->c->outfile = NULL;
		if (s->redirect_mem != 0)
		{
			s->c->isprecededbypipe = s->redirect_mem;
			s->redirect_mem = 0;
		}
	}
}

void	ft_add_args(t_mother *s, t_token *tok, int *i)
{
	t_command	*last;
	char		*temp;
	char		*temp_line;

	(void)i;
	last = ft_last_cmd(s->c);
	pre_exec_arg_checking(s, last, tok);
	if (ft_strchr("pwfqe", tok->type))
	{
		if (last->cmd_status == 1)
		{
			if (tok->type == 'f' && !(ft_strcmp(last->command, "echo")))
				check_echo_flag(s, tok);
			else if (tok->type == 'f')
				write(2, "AUCUN FLAG AUTORISÉ POUR LES BUILT-INS\n", 39);
		}
		last->nbarg++;
		ft_add_arg_array(last, tok->token);
		if (last->line == NULL)
			last->line = ft_strdup(tok->token);
		else
		{
			temp = ft_strjoin(" ", tok->token);
			temp_line = ft_strdup(last->line);
			free(last->line);
			last->line = ft_strjoin(temp_line, temp);
			free(temp);
			free(temp_line);
		}
	}
}

void	ft_add_arg_array(t_command *last, char *str)
{
	char 	**temp;
	int		len;
	int		i;

	len = ft_strlen_array(last->arg);
	temp = ft_malloc(&temp, (len + 2) * sizeof(char *));
	i = 0;
	while (i < len)
	{
		temp[i] = ft_strdup(last->arg[i]);
		i++;
	}
	temp[i++] = ft_strdup(str);
	temp[i] = NULL;
	ft_free_array(last->arg);
	last->arg = temp;
}

void	ft_add_operator(t_mother *s, t_token *tok, int *i)
{
	t_command	*last;

	last = ft_last_cmd(s->c);
	if (tok->type == 'P')
	{
		//check that last command structure is completed and next token is actually a command
		if (last->line == NULL || last->command == NULL || last->arg == NULL)
			printf("wrong pipe here, last command does not exist\n");
		if (tok->next != NULL)
		{
			if (ft_strchr("bc", tok->next->type))
				return ;
			else
				printf("pipe leads to non valid command\n"); //METTRE FT_ERROR ICI
		}
		else
			printf("pipe is last token???\n"); //METTRE FT_ERROR ICI
		
	}
	else if (tok->type == 'o')
	{
		if (tok->next != NULL)
		{
			if (ft_strchr("bcwep", tok->next->type))
				assign_redirect(s, tok, i);
			
		}
		if (tok->prev != NULL)
		{
			if (last->line != NULL && ft_strrchr("bcwefpq", tok->prev->type))
				assign_redirect(s, tok, i);
		}
	}
}

void	assign_redirect(t_mother *s, t_token *tok, int *i)
{
	t_command	*last;

	(void)i;
	last = ft_last_cmd(s->c);
	if (!(ft_strcmp(tok->token, "<")))
		s->redirect_mem = 2;
	else if (!(ft_strcmp(tok->token, ">")))
		s->redirect_mem = 3;
	else if (!(ft_strcmp(tok->token, ">>")))
		s->redirect_mem = 4;
	else if (!(ft_strcmp(tok->token, "<<")))
		s->redirect_mem = 5;
}

void	add_cmd_elem(t_mother *s, t_token *tok, int *i)
{
	t_command	*next;
	t_command	*prev;

	//printf("creating new cmd element with i = %i\n", *i);
	prev = ft_last_cmd(s->c);
	if (prev->command != NULL)
	{
		//check_pipe(); checking the existence of a pipe and creating a new cmd in case the pipe exists
		next = create_cmd(s, tok, i);
		next->previouspipe = prev;
		prev->nextpipe = next;
		next->nextpipe = NULL;
	}
	else
	{
		s->c = create_cmd(s, tok, i);
		s->c->previouspipe = NULL;
		s->c->nextpipe = NULL;
	}
}

t_command	*create_cmd(t_mother *s, t_token *tok, int *i)
{
	t_command	*new;

	(void)i;
	(void)s;
	new = ft_malloc(&new, sizeof(t_command));
	new->command = ft_strdup(tok->token);
	new->line = ft_strdup(tok->token);
	new->retvalue = 0;
	new->nbarg = 1;
	new->arg = ft_malloc(&new->arg, sizeof(char *) * 2);
	new->arg[0] = ft_strdup(tok->token);
	new->arg[1] = NULL;
	new->cmd_status = tok->type - 97;
	s->nbcmd++;
	return (new);
}

t_command	*ft_last_cmd(t_command *first)
{
	t_command	*temp;

	temp = first;
	while (temp->nextpipe != NULL)
		temp = temp->nextpipe;
	return (temp);
}

void	ft_wrong_input(t_mother *s, t_token *tok, int *i)
{
	(void)s;
	(void)tok;
	(void)i;
	//printf("INPUT NON VALIDE\n"); // METTRE FT_ERROR ICI
}
