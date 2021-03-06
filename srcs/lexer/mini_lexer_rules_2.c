/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_lexer_rules_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 20:20:25 by ogenser           #+#    #+#             */
/*   Updated: 2021/11/03 20:20:27 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_match_word(char c)
{
	if (ft_strchr("<>+-!=&|^~\\\"\'$`;", c) || c < 33 || c > 126)
		return (0);
	return (1);
}

void	ft_skip_word(t_mother *s, int *j)
{
	while (s->line[*j] && (!(ft_strchr("<>+-!=&|^~\\\"\'$`;", s->line[*j])
				|| s->line[*j] < 33 || s->line[*j] > 126)))
		*j = *j + 1;
	*j = *j - 1;
}
