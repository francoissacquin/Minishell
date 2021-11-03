/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 20:20:47 by ogenser           #+#    #+#             */
/*   Updated: 2021/11/03 20:20:53 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../inc/minishell.h"

// POUR LES TYPES DE TOKEN JE PART LA DESSUS :
// w = word
// b = built-in
// c = command
// C = command mais en path absolu
// p = path (relative or absolute)
// r = redirection
// o = operator
// P = pipe
// S = separator ie : ';'
// q = quoted string
// e = environement variable to expand ($)
// E = environment variable defined (?=?)
// f = flags (anything that starts with '-')
// d = delimiter (specifically for << redirection)

void	minilexer(t_mother *s)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s->line[j])
	{
		minilexer_inner_loop(s, &i, &j);
		if (s->line[i] == '\0' || s->line[j] == '\0')
			break ;
		j++;
	}
	if (i <= j - 1 && i < (int)ft_strlen(s->line))
		link_chain_elem(s, &i, &j, '\0');
}

void	minilexer_inner_loop(t_mother *s, int *i, int *j)
{
	if (*j > 0 && (ft_strchr("<>&|", s->line[*j - 1])
			&& !(ft_strchr("<>&|", s->line[*j]))))
		ft_new_operator_char_rule(s, i, j);
	else if (s->lex->quote == 0 && ft_strchr("\"\'", s->line[*j]))
		ft_quote_aligner(s, i, j);
	else if (s->lex->quote == 0 && ft_strchr("$`", s->line[*j]))
		ft_dollar_aligner(s, i, j);
	else if (*j > 0 && (s->lex->quote == 0
			&& ft_strchr("&|", s->line[*j - 1])))
		ft_delimiter(s, i, j, 2);
	else if (s->lex->quote == 0
		&& (s->line[*j] == '\n' || s->line[*j] == '\r'))
		link_chain_elem(s, i, j, 48);
	else if (ft_match_word(s->line[*j]))
		ft_skip_word(s, j);
	else if (*j > 0 && (ft_strchr("<>|$ ", s->line[*j])
			&& !(ft_strchr("<>|$ ", s->line[*j - 1]))))
		ft_delimiter(s, i, j, 1);
	else if (*j > 0 && (s->line[*j] == ' ' && s->line[*j - 1] == ' '))
		*i = *i + 1;
}

//creates a new token with content being the characters
//from s->line going from i to j
t_token	*create_token(t_mother *s, int i, int j, char c)
{
	t_token	*new;

	new = NULL;
	if (s->lex->token_nb == 0)
	{
		new = s->lex->first_token;
		if (j <= i)
		{
			new->token = NULL;
			new->type = '\0';
		}
		else
			new->token = ft_substr(s->line, i, j - i);
	}
	else
	{
		new = ft_malloc(&new, sizeof(t_token));
		if (j <= i)
			new->token = NULL;
		else
			new->token = ft_substr(s->line, i, j - i);
	}
	create_token_extender(s, i, c, new);
	return (new);
}

void	create_token_extender(t_mother *s, int i, char c, t_token *new)
{
	if (new->token != NULL && ft_strchr("wbcopPrSqef", c))
		new->type = c;
	else
		new->type = '\0';
	s->lex->token_nb++;
	if (i > 0 && s->line[i - 1] == ' ')
		new->pre_space = 1;
	else
		new->pre_space = 0;
}

void	create_first_token(t_mother *s, int i, int j, t_token *new)
{
	new = s->lex->first_token;
	if (j <= i)
	{
		new->token = NULL;
		new->type = '\0';
	}
	else
	{
		new->token = ft_substr(s->line, i, j - i);
	}
}
