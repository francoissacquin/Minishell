#include "../../inc/minishell.h"

void	free_t_token(t_mother *s)
{
    t_token *temp;
    t_token *next;

    temp = s->lex->first_token;
    next = NULL;
    while (temp->next != NULL)
    {
        if (temp->next != NULL)
            next = temp->next;
        if (temp->token != NULL)
            free(temp->token);
        if (temp != NULL)
            free(temp);
        temp = next;
    } 
}
