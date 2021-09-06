/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 15:59:19 by ogenser           #+#    #+#             */
/*   Updated: 2021/09/06 15:49:43 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


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

int main(int argc, char **argv, char **envp)
{
	t_mother 	s;
	
	(void)argv;
	(void)argc;
	ft_structinit(&s);
	// line = ft_malloc(&line, 1000);
	s.line = readline("Minishell> ");
	ft_history(&s);
	env_init(&s, envp);

	// ft_echo(&s);
	// ft_cd(&s);
	// ft_echo(&s);
	// printf("%s\n", s.line);
	ft_execfind(&s);
	if (ft_parse(&s) == 0)
	{
		write(1, "Error:\n", 7);
		return(0);
	}
	ft_end(&s);
	system("leaks Minishell");
	return (0);
}