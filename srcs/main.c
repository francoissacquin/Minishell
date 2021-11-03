/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 15:59:19 by ogenser           #+#    #+#             */
/*   Updated: 2021/10/22 21:53:04 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

pid_t		g_pid;

pid_t	*ft_return_global_pid(void)
{
	return (&g_pid);
}

void	ft_error(t_mother *s, char *error, int code)
{
	printf("%s ", error);
	printf("%d\n", code);
	if (code == 1)
		ft_end(s);
}

int	mainaftersignal(t_mother *s, char *str)
{
	ft_structinit(s);
	if (str == NULL)
	{
		s->line = readline("\033[1;32mMinishell> \033[0m");
		ft_add_history(s);
	}
	else
		s->line = ft_strdup(str);
	if (s->line != NULL && s->line[0] != '\0')
	{
		if (ft_lexer_handler(s))
		{
			free(s->line);
			return (s->ret);
		}
		input_output_checker(s);
		//ft_print_parsing_results(s);
	}
	else if (s->line != NULL && (s->line[0] == '\0'
			|| ft_input_is_spaces(s->line)))
		return (ft_weird_readline(s));
	else if (s->line == NULL)
		ft_control_d(s);
	exec_and_repeat(s);
	return (s->ret);
}

int	main(int argc, char **argv, char **envp)
{
	t_mother	s;
	int			exit_status;

	s.env = NULL;
	env_init(&s, envp);
	s.ret = 0;
	g_pid = 0;
	signal(SIGINT, signalhandler);
	signal(SIGQUIT, signalhandler);
	if (argc == 3)
	{
		if (!ft_strncmp(argv[1], "-c", 3))
		{
			exit_status = mainaftersignal(&s, argv[2]);
			free_t_mother(&s);
			exit(exit_status);
		}
	}
	while (1)
		mainaftersignal(&s, NULL);
	return (0);
}

void	ft_print_parsing_results(t_mother *s)
{
    t_command	*cmd;
	t_token		*tok;
	int			i;

    cmd = s->c;
	tok = s->lex->first_token;
	while (tok->next != NULL)
    {
        printf("[%s] of type [%c]\n", tok->token, tok->type);
        tok = tok->next;
    }
	printf("[%s] of type [%c]\n", tok->token, tok->type);
    printf("\n\n");
    while (cmd->nextpipe != NULL)
    {
		printf("  ||\n  ||BEFORE = %i or %i or %i\n  ||\n", cmd->isprecededbypipe, cmd->isprecededbyche, cmd->isprecededbydoubleche);
		printf("_________________________________________\n");
		if (cmd->line != NULL)
        	printf("[%s] of command [%s] with cmd_status [%c]\n", cmd->line, cmd->command, cmd->cmd_status + 97);
		else 
			printf("line is NULL\n");
		printf("Using following args =\n");
		i = 0;
		while (cmd->arg[i])
		{
			printf("||%s\n", cmd->arg[i]);
			i++;
		}
		printf(" with infile = %s and outile = %s\n", cmd->inputfile, cmd->outfile);
		printf("-----------------------------------------\n");
		printf("  ||\n  ||AFTER = %i or %i or %i\n  ||\n", cmd->isfollowedbypipe, cmd->isfollowedbyche, cmd->isfollowedbydoubleche);
        cmd = cmd->nextpipe;
    }
	printf("  ||\n  ||BEFORE = %i or %i or %i\n  ||\n", cmd->isprecededbypipe,  cmd->isprecededbyche, cmd->isprecededbydoubleche);
	printf("_________________________________________\n");
    printf("[%s] of command [%s] with cmd_status [%c]\n", cmd->line, cmd->command, cmd->cmd_status + 97);
	i = 0;
	while (cmd->arg[i])
	{
		printf("||%s\n", cmd->arg[i]);
		i++;
	}
	printf(" with infile = %s and outile = %s\n", cmd->inputfile, cmd->outfile);
	printf("-----------------------------------------\n");
	printf("  ||\n  ||AFTER = %i or %i or %i\n  ||\n", cmd->isfollowedbypipe, cmd->isfollowedbyche, cmd->isfollowedbydoubleche);
	if (s->lex->input_redir != NULL)
		printf("<< input was :\n%s\n", s->lex->input_redir);
}
