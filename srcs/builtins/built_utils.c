#include "../../inc/minishell.h"

void    ft_linking_args(t_mother *s, t_command *cmd)
{
    int     i;
    int     end;
    int     nb_spaces;
    int     nb_args;
    char    *built_in;
    char    *temp;
    char    *temp2;
    t_token *tok;

    built_in = ft_strdup(cmd->command);
    tok = s->lex->first_token;
    nb_args = ft_strlen_array(cmd->arg) - 1;
    if (nb_args < 2)
        return ;
    while (ft_strcmp(tok->token, built_in))
        tok = tok->next;
    tok = tok->next;
    i = ft_strstr_index(s->line, built_in);
    if (cmd->nextpipe != NULL)
        end = ft_strstr_index(s->line, cmd->nextpipe->arg[0]);
    else
        end = ft_strlen(s->line);
    nb_spaces = 0;
    while (s->line[i] && i < end)
    {
        if (s->line[i] == '\"' || s->line[i] == '\'')
            i = ft_skip_quote_marks(s->line, i, end);
        else if (s->line[i] != ' ')
        {
            while (s->line[i] && s->line[i] != ' ')
                i++;
        }
        else
        {
            nb_spaces++;
            while (s->line[i] && s->line[i] == ' ')
                i++;
        }
    }
    if (s->line[end] == '\0')
        nb_spaces++;
    if (nb_spaces > 2)
    {
        free(built_in);
        return ;
    }
    else
    {
        temp = NULL;
        temp2 = NULL;
        i = 1;
        while (nb_args > 1)
        {
            if (i == 1)
            {
                temp = ft_strjoin(cmd->arg[i], cmd->arg[i + 1]);
                nb_args--;
                i++;
            }
            else if (temp == NULL)
            {
                temp = ft_strjoin(temp2, cmd->arg[i + 1]);
                if (temp2 != NULL)
                {
                    free(temp2);
                    temp2 = NULL;
                }
                nb_args--;
                i++;
            }
            else if (temp2 == NULL)
            {
                temp2 = ft_strjoin(temp, cmd->arg[i + 1]);
                if (temp != NULL)
                {
                    free(temp);
                    temp = NULL;
                }
                nb_args--;
                i++;
            }
        }
        ft_free_array(cmd->arg);
        cmd->arg = ft_malloc(&cmd->arg, sizeof(char *) * 3);
        cmd->arg[0] = built_in;
        if (temp == NULL)
            cmd->arg[1] = temp2;
        else if (temp2 == NULL)
            cmd->arg[1] = temp;
        cmd->arg[2] = NULL;
    }
}

int     ft_skip_quote_marks(char *str, int i, int end)
{
    char    quote;

    quote = str[i];
    i++;
    //printf("quote %c and str[i] = %c\n", quote, str[i]);
    while (str[i] && i < end && str[i] != quote)
        i++;
    i++;
    return (i);
}

int	ft_strstr_index(char *haystack, char *needle)
{
	size_t			i;
	size_t			j;

	i = 0;
	if (!needle || needle[i] == '\0')
		return (0);
	while (haystack[i])
	{
		j = 0;
		while (needle[j] == haystack[i + j])
		{
			if (needle[j + 1] == '\0')
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}
