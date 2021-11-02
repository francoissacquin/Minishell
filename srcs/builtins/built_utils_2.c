#include "../../inc/minishell.h"

void	resolve_exit_spaces(t_command *cmd, char *built_in, int nb_args)
{
	int		i;
	char	*temp;
	char	*temp2;

	i = 1;
	temp = exit_join_args_one(cmd, &i, &nb_args);
	temp2 = NULL;
	while (nb_args > 1)
	{
		if (temp == NULL)
		{
			exit_join_arg_temp(&temp, &temp2, cmd, &i);
			nb_args--;
			i++;
		}
		else if (temp2 == NULL)
		{
			exit_join_arg_temp2(&temp, &temp2, cmd, &i);
			nb_args--;
			i++;
		}
	}
	exit_join_args(cmd, built_in, temp, temp2);
}

char	*exit_join_args_one(t_command *cmd, int *i, int *nb_args)
{
	char	*str;

	str = ft_strjoin(cmd->arg[*i], cmd->arg[*i + 1]);
	*nb_args = *nb_args - 1;
	*i = *i + 1;
	return (str);
}

void	exit_join_arg_temp(char **temp, char **temp2, t_command *cmd, int *i)
{
	*temp = ft_strjoin(*temp2, cmd->arg[*i + 1]);
	if (*temp2 != NULL)
	{
		free(*temp2);
		*temp2 = NULL;
	}
}

void	exit_join_arg_temp2(char **temp, char **temp2, t_command *cmd, int *i)
{
	*temp2 = ft_strjoin(*temp, cmd->arg[*i + 1]);
	if (*temp != NULL)
	{
		free(*temp);
		*temp = NULL;
	}
}

void	exit_join_args(t_command *cmd, char *built_in, char *temp, char *temp2)
{
	ft_free_array(cmd->arg);
	cmd->arg = ft_malloc(&cmd->arg, sizeof(char *) * 3);
	cmd->arg[0] = built_in;
	if (temp == NULL)
		cmd->arg[1] = temp2;
	else if (temp2 == NULL)
		cmd->arg[1] = temp;
	cmd->arg[2] = NULL;
}
