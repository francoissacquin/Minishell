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
		if (!(ft_strcmp(cmd->command, "env")) && cmd->nbarg == 1)
			write(2, "error, env takes no flag or argument\n", 37); // METTRE FT_ERROR ICI
	}
}

void	check_echo_flag(t_mother *s, t_token *tok)
{
	int		i;

	(void)s;
	i = 1;
	if (tok->token[0] != '-')
		return ;
	while (tok->token[i])
	{
		if (tok->token[i] != 'n')
		{
			//printf("flag non-valide pour le built-in echo\n"); //METTRE FT_ERROR ICI
			tok->type = 'w';
			return ;
		}
		i++;
	}
	if (i > 2)
	{
		tok->token = ft_strdup("-n");
	}
}
