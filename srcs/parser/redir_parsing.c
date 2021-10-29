#include "../../inc/minishell.h"

void	redir_input_handler(t_mother *s)
{
	t_token		*tok;
	int			res;
	int			ctrl;

	tok = s->lex->first_token;
	while (tok != NULL)
	{
		if (!(ft_strcmp(tok->token, "<<")) && tok->type == 'o')
		{
			res = ft_redir_error_check(s, tok);
			if (res)
				return ;
			ft_finding_delimiter(s, tok);
			ctrl = ft_redir_input_activator(s);
			if (ctrl)
				write(2, "Warning, using EOF as delimiter is not advised\n", 47);
		}
		tok = tok->next;
	}
}

void	ft_finding_delimiter(t_mother *s, t_token *tok)
{
	char	*temp;
	int		i;
	int		j;
	int		k;

	i = ft_strnstr_index(s->line, tok->token, ft_strlen(s->line));
	if (i == -1)
		printf("error, << not found in original string but << token exists\n");
	i = i + 2;
	while (s->line[i] && s->line[i] == ' ')
		i++;
	j = i;
	while (s->line[j] && s->line[j] != ' ')
		j++;
	temp = ft_malloc(&temp, (j - i + 1) * sizeof(char));
	k = 0;
	while (i < j)
	{
		if (!(s->line[i] == '\"' || s->line[i] == '\''))
			temp[k] = s->line[i];
		i++;
		k++;
	}
	temp[k] = '\0';
	s->lex->delimiter = temp;
}

int	ft_redir_error_check(t_mother *s, t_token *tok)
{
	(void)s;
	if (tok->next == NULL)
	{
		write(2, "DELIMITER IS MISSING FROM << REDIR\n", 35);
		return (1);
	}
	return (0);
}

int	ft_redir_input_activator(t_mother *s)
{
	char	*temp;
	char	*redir;

	if (s->lex->input_redir != NULL)
	{
		free(s->lex->input_redir);
		s->lex->input_redir = NULL;
	}
	temp = readline("> ");
	if (temp == NULL)
		return (1);
	while (ft_strcmp(temp, s->lex->delimiter))
	{
		ft_redir_input_loop_check(s, &temp, &redir);
		free(temp);
		temp = readline("> ");
		if (temp == NULL)
			return (1);
	}
	free(temp);
	return (0);
}

void	ft_redir_input_loop_check(t_mother *s, char **temp, char **redir)
{
	if (s->lex->input_redir == NULL)
		s->lex->input_redir = ft_strdup(*temp);
	else
	{
		*redir = ft_strjoin("\n", *temp);
		s->lex->input_redir = ft_strjoin_env(s->lex->input_redir, *redir);
		free(*redir);
	}
}
