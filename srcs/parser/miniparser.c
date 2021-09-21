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
	else if (ft_strchr("wpf", tok->type) && s->redirect_mem == 0)
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
	printf("pour passage %i on a s->redir = %i\n", *i, s->redirect_mem);
	if (tok->prev != NULL)
	{
		if (tok->prev->type == 'P')
		{
			printf("--creation post pipe avec s->redir = %i\n", s->redirect_mem);
			last->isfollowedbypipe = 1;
			add_cmd_elem(s, tok, i);
			next = ft_last_cmd(s->c);
			last->nextpipe = next;
			next->previouspipe = last;
			next->nextpipe = NULL;
			next->isprecededbypipe = 1;
			next->isfollowedbypipe = 0;
			s->pipe++;
		}
		else if (tok->prev->type == 'o' && s->redirect_mem != 0)
		{
			printf("--creation post redir avec s->redir = %i\n", s->redirect_mem);
			last->isfollowedbypipe = s->redirect_mem;
			add_cmd_elem(s, tok, i);
			next = ft_last_cmd(s->c);
			last->nextpipe = next;
			next->previouspipe = last;
			next->nextpipe = NULL;
			next->isprecededbypipe = s->redirect_mem;
			next->isfollowedbypipe = 0;
			s->pipe++;
			s->redirect_mem = 0;
		}
		else
			printf("erreur de pipe ou d'operateur, nouvelle commande sans lien devant\n"); // METTRE FT_ERROR ICI
	}
	else
	{
		printf("--creation premier element avec s->redir = %i\n", s->redirect_mem);
		s->c = create_cmd(s, tok, i);
		s->c->isfollowedbypipe = 0;
		s->c->nextpipe = NULL;
		s->c->isprecededbypipe = 0;
		s->c->previouspipe = NULL;
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

	(void)i;
	last = ft_last_cmd(s->c);
	if (ft_strchr("pwfqe", tok->type))
	{
		printf("AAAAAAHHHH pour %i\n", last->cmd_status);
		if (last->cmd_status == 'b')
		{
			printf("entering built-ins HQ\n");
			if (tok->type == 'f' && !(ft_strcmp(last->command, "echo")))
				check_echo_flag(s, tok);
			else if (tok->type == 'f')
				printf("AUCUN FLAG AUTORISÉ POUR LES BUILT-INS\n"); //METTRE FT_ERROR ICI
		}
		last->nbarg++;
		ft_add_arg_array(last, tok);
		if (last->line == NULL)
			last->line = ft_strdup(tok->token);
		else
			last->line = ft_strjoin(last->line, ft_strjoin(" ", tok->token));
	}
}

void	check_echo_flag(t_mother *s, t_token *tok)
{
	int		i;

	(void)s;
	i = 1;
	printf("WHAT?\n");
	while (tok->token[i])
	{
		if (tok->token[i] != 'n')
			printf("flag non-valide pour le built-in echo\n"); //METTRE FT_ERROR ICI
		i++;
	}
	free(tok->token);
	tok->token = ft_strdup("-n");
}

void	ft_add_arg_array(t_command *last, t_token *tok)
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
	temp[i++] = ft_strdup(tok->token);
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
			printf("wrong pipe here, lat command does not exist\n");
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
	if (last->line != NULL)
		last->isfollowedbypipe = 1;
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

	printf("creating new cmd element with i = %i\n", *i);
	prev = ft_last_cmd(s->c);
	if (prev->command != NULL)
	{
		//check_pipe(); checking the existence of a pipe and creating a new cmd in case the pipe exists
		next = create_cmd(s, tok, i);
		next->previouspipe = prev;
		prev->nextpipe = next;
		next->nextpipe = NULL;
		s->nbcmd++;
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
	printf("on a un cmd_status = %i\n", new->cmd_status);
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
	printf("INPUT NON VALIDE\n"); // METTRE FT_ERROR ICI
}
