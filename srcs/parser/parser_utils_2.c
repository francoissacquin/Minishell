#include "../../inc/minishell.h"

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

	prev = ft_last_cmd(s->c);
	if (prev->command != NULL)
	{
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
	if (tok->type == 67)
		new->cmd_status = 3;
	else
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

void	ft_wrong_input(t_mother *s)
{
	free_t_token(s);
	free_t_cmd(s);
	free_t_lexer(s);
}
