/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 12:18:17 by ogenser           #+#    #+#             */
/*   Updated: 2021/09/09 18:11:27 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_pipe(t_mother *s) // note do note foork for certain builtins
{
	// printf("hello");
	// // printf("hello%s\n", s->c->nextpipe->line);
	// printf("hello%s, %s\n", s->c->line, s->c->arg[0]);
	// printf("hello%s, %s\n", s->c->nextpipe->command, s->c->nextpipe->arg[0]);

	int i = 0;
	while (i < s->pipe)
	{
		// printf("hello%s, %s\n", s->c->line, s->c->arg[0]);
		// s->c = s->c->nextpipe;
		// int pid = dup2(1, 1);
		// ft_execfind(s);
		int status;
		pid_t pid = fork();
		if (pid < 0)
			ft_error(s, "pipe pid is shit", -1);
		if (pid == 0)
		{
			ft_execfind(s);
		}
		else
		{
			waitpid(pid, &status, 0);
		}
		
		printf("hello %s, %s\n", s->c->line, s->c->arg[0]);
		s->c = s->c->nextpipe;
		// printf("hello %s, %s\n", s->c->line, s->c->arg[0]);
		i++;
	}
		// printf("hello%s, %s\n", s->c->line, s->c->arg[0]);
	// printf("hello%s, %s\n", s->c->nextpipe->command, s->c->nextpipe->arg[0]);
	
}

void		multicommands(t_mother *s) 	//sends to different functions if its a pipe redirect etc
{	
	//testing:
	// char *c = "caca";

	t_command test;

	test.previouspipe = s->c;
	test.line = "pwd";
	test.command = "pwd";
	test.arg = ft_malloc(test.arg, sizeof(char **) * 10);
	test.arg[0] = NULL;
	test.isprecededbypipe = 1;

	s->pipe = 2;	
	s->c->line = "cat pipes.c";
	s->c->nbarg = 1;
	s->c->command = "cat";
	s->c->arg = ft_malloc(s->c->arg, sizeof(char **) * 4);
	s->c->arg[0] = s->c->command;
	s->c->arg[1] = "todo.txt";
	s->c->arg[2] = "README.md";
	s->c->arg[3] = NULL; 
	s->c->isfollowedbypipe = 1;
	s->c->nextpipe = &test;

	// test.previouspipe = s->c;
	// test.line = "grep pipe";
	// test.command = "grep";
	// test.arg = ft_malloc(test.arg, sizeof(char **) * 10);
	// test.arg[0] = "grep";
	// test.arg[1] = "pipe";
	// test.arg[2] = NULL;	
	// test.isprecededbypipe = 1;

	// char *k[4];
	// ft_bzero(k[0], sizeof(k[0]));
	// k[1] = "README.md";
	// k[2] = "todo.txt";
	// k[0] = "cat";
	// k[3] = NULL;
	// execve("/bin/cat", k, NULL);
	// ft_execfind(s);
	
	if (s->c->isfollowedbypipe == 1)
		ft_pipe(s);
	// printf("||hello");
}