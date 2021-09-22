/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 15:59:19 by ogenser           #+#    #+#             */
/*   Updated: 2021/09/16 21:28:59 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char **env;

void ft_error(t_mother *s, char * error, int code)
{
	printf("%s ", error);
	printf("%d\n", code);
	ft_end(s);
}

void	ft_history(t_mother *s)
{
	add_history(s->line);
}


int mainaftersignal(void)
{
	t_mother s;
	
	char **envp;
	envp = env;
	ft_structinit(&s);
	////ft_lexinit(&s); // on pourra combiner cette fonction a ft_structinit pus tard si on est chaud //
	// line = ft_malloc(&line, 1000);
	s.line = readline("Minishell> ");
	ft_history(&s);
	env_init(&s, envp);

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
	// t_mother 	s;
	
	(void)argv;
	(void)argc;
	env = envp;
	while (1)
	{
		signal(SIGINT, signalhandler);
		signal(SIGQUIT, signalhandler);
		mainaftersignal();
	}
	// ft_structinit(&s);
	// ////ft_lexinit(&s); // on pourra combiner cette fonction a ft_structinit pus tard si on est chaud
	// // line = ft_malloc(&line, 1000);
	// s.line = readline("Minishell> ");
	// ft_history(&s);
	// env_init(&s, envp);

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


// int main(int argc, char **argv, char **envp)
// {
//     t_mother    s;
//     t_command	*cmd;
// 	t_token		*tok;
//     (void)argv;
// 	argc = 0;
//     while (1)
//     {
// 		ft_structinit(&s);
// 		ft_initc(&s);
//         ft_lexinit(&s);
// 		env_init(&s, envp);
//         s.line = readline("Test :");
//         minilexer(&s);
//         assign_types(&s);
// 		miniparser(&s);
//         cmd = s.c;
// 		tok = s.lex->first_token;
// 		while (tok->next != NULL)
//         {
//             printf("[%s] of type [%c]\n", tok->token, tok->type);
//             tok = tok->next;
//         }
// 		printf("[%s] of type [%c]\n", tok->token, tok->type);
//         printf("\n\n");
//         while (cmd->nextpipe != NULL)
//         {
// 			printf("  ||\n  ||BEFORE = %i\n  ||\n", cmd->isprecededbypipe);
// 			printf("_________________________________________\n");
//             printf("[%s] of command [%s] with cmd_status [%c]\n", cmd->line, cmd->command, cmd->cmd_status + 97);
// 			printf("-----------------------------------------\n");
// 			printf("  ||\n  ||AFTER = %i\n  ||\n", cmd->isfollowedbypipe);
//             cmd = cmd->nextpipe;
//         }
// 		printf("  ||\n  ||BEFORE = %i\n  ||\n", cmd->isprecededbypipe);
// 		printf("_________________________________________\n");
//         printf("[%s] of command [%s] with cmd_status [%c]\n", cmd->line, cmd->command, cmd->cmd_status + 97);
// 		printf("-----------------------------------------\n");
// 		printf("  ||\n  ||AFTER = %i\n  ||\n", cmd->isfollowedbypipe);
//         //clean_struc(&s); CLEAN_STRUC DOIT ETRE REPARE, JÁI UN DOUBLE FREE JE SAIS PAS POURQUOI
//     }
//     return (0);
// }
// |=> des que on a un non flag, le reste des arguments n’est plus considéré comme des flags même si il sont lexicalement de flags?
// Rebrancher le ft_error. Surtout pour empêcher les unclosed quotes.
// Voir si on garde l’espace entre les arguments. 
// VOIR POUR LA REDIRECTION
