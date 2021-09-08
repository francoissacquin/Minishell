/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 12:20:20 by fsacquin          #+#    #+#             */
/*   Updated: 2021/09/08 11:21:03 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// dura lex sed lex.
// Sorry j'ai besoin de compiler et j'ai pas le time de debug ton code

// POUR LES TYPES DE TOKEN JE PART LA DESSUS :
// w = word
// b = built-in
// c = command
// p = path (relative or absolute)
// r = redirection
// o = operator
// P = pipe
// S = separator ie : ';'

//moved to ft_lexinit
///*
void    minilexer(t_mother *s)
{
    int     i;
    int     j;

    i = 0;
    j = 0;
    next = NULL;
    prev = NULL;
    while (s->line[j])
    {
        c = '\0';
        if (s->line[j + 1] == '\0') //if end of input is recognised
            link_chain_elem(s, &i, &j, 48);
        else if (s->line[j] == ';') // rule for separator
        {
            j--;
            link_chain_elem(s, &i, &j, 's');
            link_chain_elem(s, &i, &j, 'S');
        }
        else if (ft_strchr("<>+-!=&|^~", s->line[j - 1]) && ft_strchr("<>+-!=&|^~", s->line[j]) && s->lex->quote == 0) //adding operator as part of a bigger operation if not quoted
            link_chain_elem(s, &i, &j, 'o');
        else if (ft_strchr(s->line[j - 1], "<>+-!=&|^~") && !(ft_strchr(s->line[j], "<>+-!=&|^~"))) // if prev char is operator but new char is not, then we tokenize previous character
            link_chain_elem(s, &i, &j, 'o');
        else if (s->lex->quote == 0 && ft_strchr(s->line[j], "\\\"\'")) //opening a quoting character
            s->lex->quote = 1;
        else if (s->lex->quote == 0 && ft_strchr(s->line[j], "$`")) // see parameter expansion and $ behavior
            unquoted_parameter_expansion(s, i, j);
        else if (s->lex->quote == 0 && ft_strchr(s->line[j - 1], "<>+-!=&|^~")
        {
            j--;
            link_chain_elem(s, &i, &j, 43);
        }
        else if (s->lex->quote == 0 && (s->line[j] == '\n' || s->line[j] == '\r')) // character newline in input forces token creation
            link_chain_elem(s, &i, &j, 48);
        // normally, we put here a rule for <blank> characters, but honestly, I really can't be bothered right now.
        else if (ft_match_word(s->line[j])) // this is for word and characters with no special meaning, we iterate until the word is complete
            j = j;
        else if (s->line[j] == '#')
            s->lex->comment == 1;
        else
            i = j;
        j++;
    }
}

void    link_chain_elem(t_mother *s, int *i, int *j, char c)
{
    t_token *prev;
    t_token *next;

    prev = ft_last_elem(s->lex->first_token);
    if (prev->token != NULL)
    {
        next = create_token(s, i, j, c);
        next->prev = prev;
        prev->next = next;
        next->next = NULL;
    }
    *i = *j;
    if (c == 43 || c == 's')
        *j++;
}

t_token *create_token(t_mother *s, int i, int j, char c) //creates a new token with content being the characters from s->line going from i to j
{
    t_token *new;

    if (j <= i)
    {
        printf("weird token creation, i = %i and j = %i\n", i, j);
        new->token = NULL;
        new->type ='\0';
    }
    else
    {
        new = ft_malloc(&new, sizeof(t_token));
        new->token = ft_strdup(s->line, i, j);
        if (ft_strchr("wbcopPrS", c))
            new->type = c;
        else
            new->type = '\0';
        }
        
    }
    return (new)
}
//*/