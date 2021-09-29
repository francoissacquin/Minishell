/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 15:59:19 by ogenser           #+#    #+#             */
/*   Updated: 2021/09/28 18:29:59 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char **env;

void ft_error(t_mother *s, char * error, int code)
{
	printf("%s ", error);
	printf("%d\n", code);
	ft_clear_history();
	ft_end(s);
}

int mainaftersignal(void)
{
	t_mother s;
	
	// char **envp;
	// envp = env;
	// signal(SIGINT, SIG_IGN);
	signal(SIGINT, signalhandler);
	// signal(SIGQUIT, signalhandler);
	// signal(SIGINT, SIG_IGN);
	ft_structinit(&s);
	s.line = readline("Minishell> ");
	ft_add_history(&s);
	env_init(&s, env);

	// SI TU VEUX LANCER LE LEXER ET PARSER, ENLEVE LES COMMENTAIRES SUR LE BLOC SUIVANT. :D
	// if (s.line != NULL)
	// {
	// 	minilexer(&s);
	// 	assign_types(&s);
	// 	redir_input_handler(&s);
	// 	miniparser(&s);
	// 	ft_print_parsing_results(&s); // FONCTION POUR AFFICHER LES RESULTATS DU LEXER ET PARSER.
	// 	free(s.line);
	// 	s.line = NULL;
	// }

	// ft_echo(&s);
	// ft_cd(&s);
	// ft_echo(&s);
	// printf("%s\n", s.line);
	// ft_execfind(&s);
	multicommands(&s);
	if (ft_parse(&s) == 0)
	{
		write(1, "Error:\n", 7);
		return(0);
	}
	ft_end(&s);
	system("leaks Minishell");
	return(1);
}


int main(int argc, char **argv, char **envp)
{
	//t_mother 	s;
	
	(void)argv;
	(void)argc;
	env = envp;
	while (1)
	{
		// signal(SIGINT, signalhandler);
		// signal(SIGQUIT, signalhandler);
		//signal(SIGINT, SIG_IGN);

		mainaftersignal();
	}
	// ft_structinit(&s);
	// s.line = readline("Minishell> ");
	// ft_history(&s);
	// env_init(&s, envp);

	// SI TU VEUX LANCER LE LEXER ET PARSER, ENLEVE LES COMMENTAIRES SUR BLOC SUIVANT.
	// minilexer(&s);
	// assign_types(&s);
	// redir_input_handler(&s);
	// miniparser(&s);
	// ft_print_parsing_results(&s); // FONCTION POUR AFFICHER LES RESULTATS DU LEXER ET PARSER.

	// // ft_echo(&s);
	// // ft_cd(&s);
	// // ft_echo(&s);
	// // printf("%s\n", s.line);
	// // ft_execfind(&s);
	// multicommands(&s);
	// if (ft_parse(&s) == 0)
	// {
	// 	write(1, "Error:\n", 7);
	// 	return(0);
	// }
	// ft_end(&s);
	// system("leaks Minishell");
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
        printf("[%s] of command [%s] with cmd_status [%c]\n", cmd->line, cmd->command, cmd->cmd_status + 97);
		printf("Using following args =\n");
		i = 0;
		while (cmd->arg[i])
		{
			printf("||%s\n", cmd->arg[i]);
			i++;
		}
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
	printf("-----------------------------------------\n");
	printf("  ||\n  ||AFTER = %i\n  ||\n", cmd->isfollowedbypipe);
	if (s->lex->std_input_redir != NULL)
		printf("<< input was :\n%s\n", s->lex->std_input_redir);
    free_t_token(s); //CLEAN_STRUC DOIT ETRE REPARE, JÁI UN DOUBLE FREE JE SAIS PAS POURQUOI
}
// |=> des que on a un non flag, le reste des arguments n’est plus considéré comme des flags même si il sont lexicalement de flags?
// Rebrancher le ft_error. Surtout pour empêcher les unclosed quotes.
// Voir si on garde l’espace entre les arguments. 
// VOIR POUR LA REDIRECTION
