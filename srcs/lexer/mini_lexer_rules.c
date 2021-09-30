#include "../../inc/minishell.h"

void	ft_separator_rule(t_mother *s, int *i, int *j)
{
	if (*j - 1 > *i && s->line[*j - 1] != ' ')
        link_chain_elem(s, i, j, 's');
	while (s->line[*j + 1] == ';')
		*j = *j + 1;
	if (s->line[*j] != '\0' && s->line[*j] != ' '/* && !(ft_strchr("\0", s->line[*j + 1]))*/)
    	*j = *j + 1;
    link_chain_elem(s, i, j, 'S');
    if (s->line[*i] && s->line[*i] == ' ')
        *i = *i + 1;
	if (s->line[*j] == '\0')
		*j = *j - 1;
}

void	ft_new_operator_char_rule(t_mother *s, int *i, int *j)
{
	link_chain_elem(s, i, j, 'o');
    if (s->line[*j] == ' ')
        *i = *i + 1;;
}

void	ft_quote_aligner(t_mother *s, int *i, int *j)
{
	if (*j > *i && s->line[*j - 1] != ' ')
        link_chain_elem(s, i, j, '\0');
    quote_handler(s, i, j);
}

void	ft_dollar_aligner(t_mother *s, int *i, int *j)
{
	if (*j - 1 > *i && s->line[*j - 1] != ' ')
        link_chain_elem(s, i, j, '\0');
    dollar_tokeniser(s, i, j);
}

void	ft_delimiter(t_mother *s, int *i, int *j, int o)
{
	if (o == 1)
	{
		link_chain_elem(s, i, j, '\0');
    	if (s->line[*j] == ' ')
    	   *i = *i + 1;
	}
	else if (o == 2)
	{
		j--;
        link_chain_elem(s, i, j, 43);
	}
}
