#include "../../inc/minishell.h"
/*
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
}

void	ft_tok_conveyor_belt(t_mother *s, t_token *tok, int *i)
{
	if (i == 0 && ft_strchr("pf", tok->type))
		ft_wrong_input(s, tok, i);
	else if (ft_strchr("cb", tok->type))
		ft_cmd_blt(s, tok, i);
	else if (ft_strchr("Po", tok->type))
		ft_add_operator(s, tok, i); // A FAIRE
	else if (ft_strchr("wpef", tok->type))
		ft_add_args(s, tok, i);// A FAIRE
	else if (tok->type == 'e')
		ft_env_handler(s, tok, i); // A FAIRE
}

void	ft_cmd_blt(t_mother *s, t_token *tok, int *i)
{
	t_command	*last;
	t_command	*next;

	last = ft_last_cmd(s->c);
	if (tok->prev != NULL)
	{
		if (tok->prev->type = 'P')
		{
			last->isfollowedbypipe = 1;
			add_cmd_elem(s, tok, i);
			next = t_last_cmd(s->c);
			last->nextpipe = next;
			next->previouspipe = last;
			next->isprecededbypipe = 1;
			next->isfollowedbypipe = 0;
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
		s->pipe++;
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

	new = ft_malloc(&new, sizeof(t_command));
	new->command = ft_strdup(tok->token);
	new->line = ft_strdup(tok->token);
	new->retvalue = 0;
	new->nbarg = 1;
	new->arg = ft_malloc(&new->arg, sizeof(char **) * 2);
	new->arg[0] = ft_strdup(tok->token);
	new->arg[1] = NULL;
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
*/