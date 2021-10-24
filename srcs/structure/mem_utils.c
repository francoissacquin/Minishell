#include "../../inc/minishell.h"

void	free_t_token(t_mother *s)
{
    t_token *temp;
    t_token *next;

    if (s->lex->first_token == NULL)
        return ;
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
    if (temp->next != NULL)
        next = temp->next;
    if (temp->token != NULL)
        free(temp->token);
    if (temp != NULL)
        free(temp);
    //printf("free_t_token activated\n");
}


void    free_t_lexer(t_mother *s)
{
    if (s->lex->delimiter != NULL)
        free(s->lex->delimiter);
    if (s->lex->std_input_redir != NULL)
        free(s->lex->std_input_redir);
    free(s->lex);
}

void    free_t_mother(t_mother *s)
{
    free(s->path);
    ft_free_array(s->env);
}

void    free_t_cmd(t_mother *s)
{
    t_command   *temp;
    t_command   *next;

    if (s->c == NULL)
        return ;
    temp = s->c;
    next = NULL;
    while (temp->nextpipe != NULL)
    {
        if (temp->nextpipe != NULL)
            next = temp->nextpipe;
        free_one_cmd(s, temp);
        temp = next;
    }
    free_one_cmd(s, temp);
    //free(s->c);
    //printf("free_t_command activated\n");
}

void    free_one_cmd(t_mother *s, t_command *temp)
{
    (void)s;
    if (temp->line != NULL)
        free(temp->line);
    if (temp->command != NULL)
        free(temp->command);
    if (ft_strlen_array(temp->arg) > 0)
        ft_free_array(temp->arg);
    if (temp->previouspipe != NULL)
        temp->previouspipe = NULL;
    if (temp->outfile != NULL)
        free(temp->outfile);
    if (temp->inputfile != NULL)
        free(temp->inputfile);
    if (temp != NULL)
        free(temp);
    temp = NULL;
}
