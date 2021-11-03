/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_lst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 20:20:11 by ogenser           #+#    #+#             */
/*   Updated: 2021/11/03 20:20:12 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*ft_last_elem(t_token *token)
{
	t_token	*temp;

	temp = token;
	if (!temp)
		return (NULL);
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

void	link_chain_elem(t_mother *s, int *i, int *j, char c)
{
	t_token		*prev;
	t_token		*next;
	int			temp_i;
	int			temp_j;

	prev = ft_last_elem(s->lex->first_token);
	temp_i = *i;
	temp_j = *j;
	if (prev->token != NULL)
	{
		next = create_token(s, temp_i, temp_j, c);
		next->prev = prev;
		prev->next = next;
		next->next = NULL;
	}
	else
	{
		s->lex->first_token = create_token(s, temp_i, temp_j, c);
		s->lex->first_token->prev = NULL;
		s->lex->first_token->next = NULL;
	}
	*i = temp_j;
	if (c == 43 || c == 's')
		*j = temp_j + 1;
}

void	quote_handler(t_mother *s, int *i, int *j)
{
	char	quote;

	quote = s->line[*j];
	*i = *j;
	*j = *j + 1;
	while (s->line[*j] && s->line[*j] != quote)
		*j = *j + 1;
	if (s->line[*i] == '\0' || s->line[*j] == '\0')
		return ;
	if (s->line[*j] == quote)
	{
		*j = *j + 1;
		link_chain_elem(s, i, j, 'q');
	}
	if (s->line[*i] == ' ')
		*i = *i + 1;
	if (s->line[*j] == '\0')
		return ;
	if (ft_strchr("\"\'", s->line[*j]) && s->line[*j + 1] != '\0')
		ft_quote_aligner(s, i, j);
}

void	dollar_tokeniser(t_mother *s, int *i, int *j)
{
	*i = *j;
	*j = *j + 1;
	while (s->line[*j] && (ft_isalnum(s->line[*j])
			|| ft_strchr("_=+-?", s->line[*j])))
		*j = *j + 1;
	link_chain_elem(s, i, j, 'e');
	if (s->line[*i] == ' ')
		*i = *i + 1;
	if (s->line[*j] != ' ')
		*j = *j - 1;
}
