#include "../../inc/minishell.h"

void	ft_linking_args(t_mother *s, t_command *cmd)
{
	int		end;
	int		nb_spaces;
	int		nb_args;
	char	*built_in;

	built_in = ft_strdup(cmd->command);
	nb_args = ft_strlen_array(cmd->arg) - 1;
	if (nb_args < 2)
		return ;
	if (cmd->nextpipe != NULL)
		end = ft_strstr_index(s->line, cmd->nextpipe->arg[0]);
	else
		end = ft_strlen(s->line);
	nb_spaces = ft_exit_arg_spaces(s, ft_strstr_index(s->line, built_in), end);
	if (nb_spaces > 2)
	{
		free(built_in);
		return ;
	}
	else
		resolve_exit_spaces(cmd, built_in, nb_args);
}

int	ft_exit_arg_spaces(t_mother *s, int i, int end)
{
	int		nb_spaces;

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
	return (nb_spaces);
}

int	ft_skip_quote_marks(char *str, int i, int end)
{
	char	quote;

	quote = str[i];
	i++;
	while (str[i] && i < end && str[i] != quote)
		i++;
	i++;
	return (i);
}

int	ft_strstr_index(char *haystack, char *needle)
{
	size_t	i;
	size_t	j;

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
