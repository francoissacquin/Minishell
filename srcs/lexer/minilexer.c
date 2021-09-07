/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsacquin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 12:20:20 by fsacquin          #+#    #+#             */
/*   Updated: 2021/09/07 12:20:23 by fsacquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void    minilexer(t_mother *s)
{
    int     i;
    int     j;

    i = 0;
    j = 0;
    while (s->line[j])
    {
        if (s->line[j + 1] == '\0') //if end of input is recognised
            end_input(s, i, j);
        else if (ft_match_op(s->line[j - 1]) && ft_match_op(s->line[j] && s->lexer->quote == 0) //adding operator as part of a bigger operation if not quoted
            operator_token(s, i, j);
        
        j++;
    }
}

void    end_input(t_mother *s, int i, int j)
{
    if (j <= i)
    {
        s->
    }
}