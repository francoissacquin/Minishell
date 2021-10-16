#include "../../inc/minishell.h"

void	pre_exec_arg_checking(t_mother *s, t_command *cmd, t_token *tok)
{
	(void)s;
	if (cmd->command == NULL)
		return ;
	if (!(ft_strcmp("echo", cmd->command)) && tok->type == 'f')
		return ;
	else if (cmd->cmd_status == 1)
	{
		if (!(ft_strcmp(cmd->command, "export")) && !(ft_strchr("E", tok->type)))
			write(2, "error, invalid argument was given to export, non valid env variable\n", 68);
		else if (!(ft_strcmp(cmd->command, "env")) && cmd->nbarg == 1)
			write(2, "error, env takes no flag or argument\n", 37); // METTRE FT_ERROR ICI
	}
}

void	check_echo_flag(t_mother *s, t_token *tok)
{
	int		i;
	int		wrong_flag;

	(void)s;
	i = 1;
	wrong_flag = 0;
	if (tok->token[0] != '-')
		return ;
	while (tok->token[i])
	{
		if (tok->token[i] != 'n')
		{
			//printf("flag non-valide pour le built-in echo\n"); //METTRE FT_ERROR ICI
			wrong_flag = 1;
		}
		i++;
	}
	if (!wrong_flag)
	{
		free(tok->token);
		tok->token = ft_strdup("-n");
	}
}
