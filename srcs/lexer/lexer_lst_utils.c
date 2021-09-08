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


