/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 15:59:19 by ogenser           #+#    #+#             */
/*   Updated: 2021/10/04 15:12:46 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//static char **env;

void ft_error(t_mother *s, char * error, int code)
{
	printf("%s ", error);
	printf("%d\n", code);
	if (code == 1)
		ft_end(s);
}

int mainaftersignal(t_mother *s, char *str)
{
	//int pid = getpid();
	//printf("\noooglobal pid = %dooo\n", pid);
	// char **envp;
	// envp = env;
	// signal(SIGINT, SIG_IGN);
	signal(SIGINT, signalhandler);
	// signal(SIGQUIT, signalhandler);
	// signal(SIGINT, SIG_IGN);
	ft_structinit(s);
	if (str == NULL)
	{
		s->line = readline("Minishell> ");
		ft_add_history(s);
	}
	else
		s->line = str;
	// SI TU VEUX LANCER LE LEXER ET PARSER, ENLEVE LES COMMENTAIRES SUR LE BLOC SUIVANT. :D
	if (s->line != NULL && s->line[0] != '\0')
	{
		minilexer(s);
		assign_types(s);
		redir_input_handler(s);
		miniparser(s);
		//ft_print_parsing_results(s); // FONCTION POUR AFFICHER LES RESULTATS DU LEXER ET PARSER.
		//free(s->line);
		//s->line = NULL;
	}
	// ft_end(s);
	// ft_echo(s);
	// ft_cd(s);
	// ft_echo(s);
	// printf("%s\n", s->line);
	// ft_execfind(s);
	multicommands(s);
	if (ft_parse(s) == 0)
	{
		write(1, "Error:\n", 7);
		return(s->ret);
	}
	free_t_token(s);
	free_t_cmd(s);
	free_t_lexer(s);
	//free_t_mother(s);
	if (str == NULL)
		free(s->line);
	// system("leaks Minishell");
	return(s->ret);
}


int main(int argc, char **argv, char **envp)
{
	t_mother 	s;
	
	// if (envp != NULL)
	// 	env = envp;
	// else
	// {
	// 	printf("What are you trying to do exactly?????\n");
	// 	exit(0);
	// }
	s.env = NULL;
	env_init(&s, envp);
	s.ret = 0;
	if (argc == 3)
	{
		if (!ft_strncmp(argv[1], "-c", 3))
		{
    		int exit_status = mainaftersignal(&s, argv[2]);
			ft_free_array(s.env);
			free(s.path);
    		exit(exit_status);
		}
	}
	while (1)
	{
		// signal(SIGINT, signalhandler);
		// signal(SIGQUIT, signalhandler);
		//signal(SIGINT, SIG_IGN);
		mainaftersignal(&s, NULL);
	}
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
		printf("  ||\n  ||BEFORE = %i\n  ||\n", cmd->isprecededbypipe);
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
		printf("  ||\n  ||AFTER = %i\n  ||\n", cmd->isfollowedbypipe);
        cmd = cmd->nextpipe;
    }
	printf("  ||\n  ||BEFORE = %i\n  ||\n", cmd->isprecededbypipe);
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
	printf("  ||\n  ||AFTER = %i\n  ||\n", cmd->isfollowedbypipe);
	if (s->lex->std_input_redir != NULL)
		printf("<< input was :\n%s\n", s->lex->std_input_redir);
}
// |=> des que on a un non flag, le reste des arguments n’est plus considéré comme des flags même si il sont lexicalement de flags?
// Rebrancher le ft_error. Surtout pour empêcher les unclosed quotes.
// Voir si on garde l’espace entre les arguments. 
// VOIR POUR LA REDIRECTION
