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
	s->c->cmd_status = tok->type - 97;
	s->nbcmd++;
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
