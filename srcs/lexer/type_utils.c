#include "../../inc/minishell.h"

int	ft_is_op_redir(char *str)
{
	int	i;

	i = 0;
	if (str == NULL || str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (!(ft_strchr("<>|", str[i])))
			return (0);
		i++;
	}
	return (1);
}

int	ft_stat_check_path(char *str)
{
	int			i;
	struct stat	sb;

	i = stat(str, &sb);
	return (i);
}
