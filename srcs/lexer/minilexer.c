/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 12:20:20 by fsacquin          #+#    #+#             */
/*   Updated: 2021/09/08 11:10:03 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// dura lex sed lex.
// Sorry j'ai besoin de compiler et j'ai pas le time de debug ton code


void    lex_init(t_mother *s)
{
    s->lex->quote = 0;
    s->lex->comment = 0;
}

// void    minilexer(t_mother *s)
// {
//     int     i;
//     int     j;

//     i = 0;
//     j = 0;
//     while (s->line[j])
//     {
//         if (s->line[j + 1] == '\0') //if end of input is recognised
//             create_token(s, i, j);
//         else if (ft_match_op(s->line[j - 1]) && ft_match_op(s->line[j] && s->lex->quote == 0) //adding operator as part of a bigger operation if not quoted
//             create_token(s, i, j);
//         else if (ft_strchr(s->line[j - 1], "<>+-!=&|^~") && !(ft_strchr(s->line[j], "<>+-!=&|^~"))) // if prev char is operator but new char is not, then ze tokenize previous character
//             create_token(s, i, j);
//         else if (s->lex->quote == 0 && ft_strchr(s->line[j], "\\\"\'")) //opening a quoting character
//             s->lex->quote = 1;
//         else if (s->lex->quote == 0 && ft_strchr(s->line[j], "$`")) // see pararmeter expamsion and $ behavior
//             unquoted_parameter_expansion(s, i, j);
//         else if (s->lex->quote == 0 && ft_strchr(s->line[j - 1], "<>+-!=&|^~")
//             create_token(s, i, j - 1);
//         else if (s->lex->quote == 0 && (s->line[j] == '\n' || s->line[j] == '\r')) // character newline in input forces token creation
//             create_token(s, i, j);
//         // normally, we put here a rule for <blank> characters, but honestly, I really can't be bothered right now.
//         else if (ft_match_word(s->line[j])) // this is for word and characters with no special meaning, we iterate until the word is complete
//             j = j;
//         else if (s->line[j] == '#')
//             s->lex->comment == 1;
//         else
//             i = j;
//         j++;
//     }
// }

// void    create_token(t_mother *s, int i, int j) //creates a new token with content being the characters from s->line going from i to j
// {
//     if (j <= i)
//     {
//     }
// }