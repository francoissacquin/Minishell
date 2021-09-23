#include "../../inc/minishell.h"

void	redir_input_handler(t_mother *s)
{
	t_token		*tok;

	tok = s->lex->first_token;
	while(tok->next != NULL)
	{
		if (!(ft_strcmp(tok->token, "<<")) && tok->type == 'o')
		{
			//LANCER LE READLINE EN BOUCLE
			ft_finding_delimiter(s, tok);
			ft_redir_error_check(s, tok);
			ft_redir_input_activator(s);
		}
		tok = tok->next;
	}
	if (!(ft_strcmp(tok->token, "<<")) && tok->type == 'o')
	{
		//LANCER LE READLINE EN BOUCLE
		ft_finding_delimiter(s, tok);
		ft_redir_error_check(s, tok);
		ft_redir_input_activator(s);
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
		printf("error, << not found in original string but << token exists\n"); //METTRE FT_ERROR ICI
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
	printf("delimiter = %s\n", s->lex->delimiter);
}

void	ft_redir_error_check(t_mother *s, t_token *tok)
{
	(void)s;
	(void)tok;
	if (tok->next == NULL)
		printf("DELIMITER IS MISSING FROM << REDIR\n"); // METTRE FT_ERROR ICI
}

void	ft_redir_input_activator(t_mother *s)
{
	char	*temp;

	if (s->lex->std_input_redir != NULL)
	{
		free(s->lex->std_input_redir);
		s->lex->std_input_redir = NULL;
	}
	temp = readline("> ");
	while (ft_strcmp(temp, s->lex->delimiter))
	{
		if (s->lex->std_input_redir == NULL)
			s->lex->std_input_redir = ft_strdup(temp);
		else
		{
			s->lex->std_input_redir = ft_strjoin_env(s->lex->std_input_redir, ft_strjoin("\n", temp));
		}
		free(temp);
		temp = readline("> ");
	}
}

int		ft_strnstr_index(char *haystack, char *needle, int len)
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