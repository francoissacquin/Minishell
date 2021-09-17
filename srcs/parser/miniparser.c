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
	else if (ft_strchr("wpf", tok->type))
		ft_add_args(s, tok, i);// A FAIRE
	else if (tok->type == 'e')
	{
		printf("yo\n");
		//ft_env_handler(s, tok, i); // A FAIRE
	}
}

void	ft_cmd_blt(t_mother *s, t_token *tok, int *i)
{
	t_command	*last;
	t_command	*next;

	last = ft_last_cmd(s->c);
	if (tok->prev != NULL)
	{
		if (tok->prev->type == 'P')
		{
			last->isfollowedbypipe = 1;
			add_cmd_elem(s, tok, i);
			next = ft_last_cmd(s->c);
			last->nextpipe = next;
			next->previouspipe = last;
			next->isprecededbypipe = 1;
			next->isfollowedbypipe = 0;
			s->pipe++;
		}
		else
			printf("erreur de pipe, nouvelle commande sans pipe devant\n"); // METTRE FT_ERROR ICI
	}
	else
	{
		s->c = create_cmd(s, tok, i);
		s->c->isfollowedbypipe = 0;
		s->c->nextpipe = NULL;
		s->c->isprecededbypipe = 0;
		s->c->previouspipe = NULL;
	}
}

void	ft_add_args(t_mother *s, t_token *tok, int *i)
{
	t_command	*last;

	(void)i;
	last = ft_last_cmd(s->c);
	if (ft_strchr("pwf", tok->type))
	{
		last->nbarg++;
		ft_add_arg_array(last, tok);
		last->line = ft_strjoin(last->line, ft_strjoin(" ", tok->token));
	}
}

void	ft_add_arg_array(t_command *last, t_token *tok)
{
	char 	**temp;
	int		len;
	int		i;

	len = ft_strlen_array(last->arg);
	printf("len = %i pour tok = %s et type = %c\n", len, tok->token, tok->type);
	temp = ft_malloc(&temp, (len + 2) * sizeof(char *));
	i = 0;
	while (i < len)
	{
		temp[i] = ft_strdup(last->arg[i]);
		i++;
	}
	temp[i++] = tok->token;
	temp[i] = NULL;
	ft_free_array(last->arg);
	last->arg = temp;
}

void	ft_add_operator(t_mother *s, t_token *tok, int *i)
{
	t_command	*last;

	(void)i;
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
			printf("pipe is last token???\n");
		
	}
	else if (tok->type == 'o')
	{
		//check if redirection or something else
	}
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
}
