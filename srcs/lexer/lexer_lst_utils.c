#include "../../inc/minishell.h"

t_token *ft_last_elem(t_token *token)
{
    t_token *temp;

    temp = token;
    if (!temp)
        return (NULL);
    while (temp->next != NULL)
        temp = temp->next;
    return (temp);
}

void    quote_handler(t_mother *s, int *i, int *j)
{
    char    quote;

    quote = s->line[*j];
    *i = *j;
    *j = *j + 1;
    while (s->line[*j] && s->line[*j] != quote)
        *j = *j + 1;
    if (s->line[*i] == '\0' || s->line[*j] == '\0')
    {
        printf("unfinished quotes\n"); // METTRE FT_ERROR ICI
        return ;
    }
    if (s->line[*j] == quote)
    {
        *j = *j + 1;
        link_chain_elem(s, i, j, 'q');
    }
    if (s->line[*i] == ' ')
        *i = *i + 1;
    printf("handler :j = %i et i = %i\n", *j, *i);
    if (s->line[*j] == '\0')
        return ;
    if (ft_strchr("\"\'", s->line[*j]) && s->line[*j + 1] != '\0')
        ft_quote_aligner(s, i, j);
}

void    dollar_tokeniser(t_mother *s, int *i, int *j)
{
    *i = *j;
    *j = *j + 1;
    while (s->line[*j] && (ft_isalnum(s->line[*j]) || ft_strchr("_=+-", s->line[*j])))
        *j = *j + 1;
    link_chain_elem(s, i, j, 'e');
    if (s->line[*i] == ' ')
        *i = *i + 1;
    if (s->line[*j] != ' ')
        *j = *j - 1;
}
