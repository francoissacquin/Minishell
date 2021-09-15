/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 12:18:17 by ogenser           #+#    #+#             */
/*   Updated: 2021/09/15 18:52:44 by ogenser          ###   ########.fr       */
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
	// while (i < s->pipe)
	{

	// 		t_command test;

	// test.previouspipe = s->c;
	// test.line = "wc";
	// test.command = "wc";
	// test.arg = ft_malloc(test.arg, sizeof(char **) * 10);
	// test.arg[0] = test.command;
	// test.arg[1] = NULL;
	// test.arg[2] = NULL;
	// test.isprecededbypipe = 1;
	
		// int pipes[2];
		int status;
		if(pipe(s->c->pipes) == -1)
			ft_error(s, "pipe", -1);
		int pid = fork();
		if(pid < 0)
			ft_error(s, "fork", -1);
		if (pid < 0)
			ft_error(s, "pipe pid is shit", -1);
		if (pid == 0)
		{
			//child
			puts("HELLO");
			// close(pipes[1]); //close read side
			// dup2(pipes[0], 0); //connect write to stdout
			// close(pipes[0]);
			if(s->c->previouspipe)
				dup2(s->c->previouspipe->pipes[0], 0); //fermer celui d'avant
			dup2(s->c->pipes[1], 1); //dup stdout sur la commande actuelle

			// s->c = s->c->nextpipe;
			printf("hello %s, %s\n", s->c->line, s->c->arg[0]);
			ft_execfind(s, s->c->nextpipe);
			write(2, "hello\n", 6);
		}
		else
		{
			//parent
			waitpid(pid, &status, 0);
			puts("CACA");
			// if ()
			close(s->c->pipes[0]); //close write side
			//dup2(s->c->pipes[1], 1); //connect read to stdin
			// pas de dup juste des close pipe0 prv0 et 1;
			close(s->c->pipes[1]); //close read
			ft_execfind(s, s->c);
			//close pipes
			// if(s->c->isprecededbypipe)
			// 	close(s->c->previouspipe->)
		}
		// printf("hello %s, %s\n", s->c->line, s->c->arg[0]);
		// s->c = s->c->nextpipe;
		printf("hello %s, %s\n", s->c->line, s->c->arg[0]);
		i++;
	}
	
}

void		ft_pipe2(t_command *c, t_mother *s)
{
	int status;
	int err = 0;

	// if(c->isfollowedbypipe || c->isprecededbypipe)
		err = pipe(c->pipes);
	if(err != 0)
		ft_error(s, "pipe", -1);
	int pid = fork();
	if(pid < 0)
		ft_error(s, "fork", -1);
	if (pid < 0)
		ft_error(s, "pipe pid is shit", -1);
	if(pid == 0)
	{
		puts("CHILD");
		if (c->isfollowedbypipe)
		{
			puts("CAS 1");
			err = dup2(c->pipes[1], 1); //on branche le write side to stdout
			if (err < 0)
				ft_error(s, "pipe dup2", -1);
		}
		else if (c->isprecededbypipe)
		{
			puts("CAS 2");
			err = dup2(c->pipes[0], 0); //connect read side to stdin
			if (err < 0)
				ft_error(s, "pipe dup2", -1);
			// dup2(c->previouspipe->pipes[0], 1);
			// exit(0);
		}
		ft_execfind(s, s->c);
		exit(0);
	}
	else
	{
		puts("CACA");
		printf("hello %s, %s\n", c->line, c->arg[0]);
		// (void)status;
		waitpid(pid, &status, 0);
		if(c->isfollowedbypipe) // || c->isprecededbypipe)
		{
			if (c->isfollowedbypipe)
			{
				puts("CAS 5");
				close(c->pipes[1]); // si suivi par un pipe on close write side
			}
			if (c->nextpipe == NULL)
			{
				puts("CAS 4");
				close(c->pipes[0]); //si suivi par rien on close le read side
			}
		}
		if (c->isprecededbypipe)
		{
			puts("CAS 3");
			close(c->previouspipe->pipes[0]);
		}
		// exit(0);
		
	}
	

}

void		multicommands(t_mother *s) 	//sends to different functions if its a pipe redirect etc
{	
	//testing:
	// char *c = "caca";

// cat todo.txt | grep pipe | wc

	// t_command test2;
	// t_command test;

	// test2.previouspipe = s->c->nextpipe;
	// test2.line = "wc";
	// test2.command = "wc";
	// test2.arg = ft_malloc(test2.arg, sizeof(char **) * 10);
	// test2.arg[0] = test2.command;
	// test2.arg[1] = NULL;
	// test2.arg[2] = NULL;
	// test2.isprecededbypipe = 1;
	// test2.previouspipe = &test;
	// test2.isfollowedbypipe = 0;
	// test2.nextpipe = NULL;
	
	// test.previouspipe = s->c;
	// test.line = "grep pipe";
	// test.command = "grep";
	// test.arg = ft_malloc(test.arg, sizeof(char **) * 10);
	// test.arg[0] = test.command;
	// test.arg[1] = "grep";
	// test.arg[2] = NULL;
	// test.isfollowedbypipe = 1;
	// test.nextpipe = &test2;
	// test.isprecededbypipe = 1;
	// test.previouspipe = s->c;

	// s->pipe = 3;	
	// s->c->line = "cat todo.txt";
	// s->c->nbarg = 1;
	// s->c->command = "cat";
	// s->c->arg = ft_malloc(s->c->arg, sizeof(char **) * 4);
	// s->c->arg[0] = s->c->command;
	// s->c->arg[1] = "todo.txt";
	// s->c->arg[2] = NULL;
	// s->c->arg[3] = NULL; 
	// s->c->isfollowedbypipe = 1;
	// s->c->isprecededbypipe = 0;
	// s->c->nextpipe = &test;

	t_command test;

	test.previouspipe = s->c;
	test.line = "grep pipe";
	test.command = "grep";
	test.arg = ft_malloc(test.arg, sizeof(char **) * 10);
	test.arg[0] = test.command;
	test.arg[1] = "grep";
	test.arg[2] = NULL;
	test.isfollowedbypipe = 0;
	test.nextpipe = NULL;
	test.isprecededbypipe = 1;
	test.previouspipe = s->c;

	s->pipe = 1;	
	s->c->line = "cat todo.txt";
	s->c->nbarg = 1;
	s->c->command = "cat";
	s->c->arg = ft_malloc(s->c->arg, sizeof(char **) * 4);
	s->c->arg[0] = s->c->command;
	s->c->arg[1] = "todo.txt";
	s->c->arg[2] = NULL;
	s->c->arg[3] = NULL; 
	s->c->isfollowedbypipe = 1;
	s->c->isprecededbypipe = 0;
	s->c->nextpipe = &test;

	// int i = 0;
	// while (i < 3)
	// {
	// 	printf("hello %s, %s\n", s->c->line, s->c->arg[0]);
	// 	s->c = s->c->nextpipe;
	// 	i++;
	// }
	// exit(0);
// ft_execfind(s);
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
	

	// if (s->c->isfollowedbypipe == 1)
	// 	ft_pipe(s);
	t_mother *tmp;
	// int ret = 0;
	int i = 0;
	while(i < 2)
	{
		tmp = s;
		puts("ZGEG");
		ft_pipe2(s->c, tmp);
		if(!s->c->nextpipe)
			break;
		s->c = s->c->nextpipe;
		i++;
	}
	// printf("||hello");
}