#include "../../inc/minishell.h"

int     ft_find_equal_sign(char *str)
{
    int     i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '=')
            return (i);
        i++;
    }
    return (-1);
}
