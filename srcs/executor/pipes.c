/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 12:18:17 by ogenser           #+#    #+#             */
/*   Updated: 2021/09/28 18:42:57 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void		ft_child(t_command *c, t_mother *s)
{
	int err = 0;
	int fd = 0;

	if (c->isfollowedbypipe > 1)
	{
		printf("hello\n");
		printf("%s\n", c->outfile);
		if (c->isfollowedbypipe == 3)
			fd = open(c->outfile, O_RDWR|O_CREAT, 0666);
		if (c->isfollowedbypipe == 4)
			fd = open(c->outfile, O_RDWR|O_APPEND|O_CREAT, 0666);
		printf("%d\n", fd);
		if (c->isfollowedbypipe == 3 || c->isfollowedbypipe == 4)
			err = dup2(fd, 1);
		if (err < 0)
			ft_error(s, "redirect dup2", -1);
		if (c->isfollowedbypipe == 3 || c->isfollowedbypipe == 4)
			err = dup2(fd, 2);
		if (err < 0)
			ft_error(s, "redirect dup2", -1);
		if (c->isfollowedbypipe == 2)
		{
			printf("caca");
			fd = open(c->inputfile, O_RDWR|O_APPEND, 0666);
			printf("%d\n", fd);
			err = dup2(fd, 0);
			close(c->pipes[1]);
			//write(0, "test redir dup2", 16);
			if (err < 0)
				ft_error(s, "pipe dup2", -1);
			close(fd);
			//connect read side to stdin
		}
	}
	if (c->isprecededbypipe) //si y'a un pipe avant on connecte la sortie du pipe au stdin
	{
		err = dup2(c->previouspipe->pipes[0], 0); //connect read side to stdin
		if (err < 0)
			ft_error(s, "pipe dup2", -1);
	}
	if (c->isfollowedbypipe == 1) // si pipe apres on branche l'entree du pipe sur le stdout
	{
		err = dup2(c->pipes[1], 1); //on branche le write side to stdout
		if (err < 0)
			ft_error(s, "pipe dup2", -1);
	}
	if(fd)
		close(fd);
	ft_execfind(s, s->c); //execute command in child process meme si il y'en a que une
	exit(1);
}

void		ft_parent(t_command *c, int pid)
{
	int status;

	if (c->isprecededbypipe)
		close(c->previouspipe->pipes[0]); // peut etre a mettre a la fin // on ferme le pipe d'avant
	if(c->isfollowedbypipe == 1|| c->isprecededbypipe || c->isfollowedbypipe == 3)
	{
		close(c->pipes[1]); // si suivi ou apres par un pipe on close write side
	if (c->isfollowedbypipe == 3)
	{
		printf("hello\n");
		int fd;
		// int err;
		printf("%s\n", c->outfile);
		fd = open(c->outfile, O_RDWR|O_CREAT, 0666);
		printf("%d\n", fd);
		// write(fd, "chib", 4);
		// err = dup2(c->pipes[1], 3); //on branche le write side to stdout
		// close(c->pipes[0]);
		// if (err < 0)
		// 	{
		// 		printf("exxor");
		// 		exit(0);}

	}
		if (c->nextpipe == NULL) //si c'est le dernier // histoire de propreté plus que de necessité
		{
			dup2(c->pipes[1], 0); // on branche la sortie du pipe sur stdin pour imprimer
			close(c->pipes[0]); //si suivi par rien on close le read side
		}
	}
	waitpid(pid, &status, 0); //peut etre a mettre au debut	du parent // on attends la fin du child pour etre sur d'avoir tte la sortie
}



void		ft_pipe(t_command *c, t_mother *s)
{
	int err = 0;
	// int ret = 1;
	int pid;

	if(c->isfollowedbypipe == 1|| c->isprecededbypipe)
		err = pipe(c->pipes);
	if(err != 0)
		ft_error(s, "pipe", -1);
	pid = fork();
	if(pid < 0)
		ft_error(s, "fork", -1);
	if (pid < 0)
		ft_error(s, "pipe pid is shit", -1);
	if(pid == 0)
		ft_child(c, s);
	else
		ft_parent(c, pid);
}

void		multicommands(t_mother *s) 	//sends to different functions if its a pipe redirect etc
{	
	//testing:
	// char *c = "caca";

// cat todo.txt | grep pipe | wc


//test with 3
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

	// s->pipe = 2;
	// s->nbcmd = 3;	
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

//test with 2
	// t_command test;

	// test.previouspipe = s->c;
	// test.line = "grep pipe";
	// test.command = "grep";
	// test.arg = ft_malloc(test.arg, sizeof(char **) * 10);
	// test.arg[0] = test.command;
	// test.arg[1] = "pipe";
	// test.arg[2] = NULL;
	// test.isfollowedbypipe = 0;
	// test.nextpipe = NULL;
	// test.isprecededbypipe = 1;
	// test.previouspipe = s->c;

	// s->pipe = 1;	
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

//other test 2
	// t_command test;

	// test.previouspipe = s->c;
	// test.line = "wc";
	// test.command = "wc";
	// test.arg = ft_malloc(test.arg, sizeof(char **) * 10);
	// test.arg[0] = test.command;
	// test.arg[1] = NULL;
	// test.isfollowedbypipe = 0;
	// test.nextpipe = NULL;
	// test.isprecededbypipe = 1;
	// test.previouspipe = s->c;

	// s->pipe = 1;	
	// s->c->line = "ls";
	// s->c->nbarg = 1;
	// s->c->command = "ls";
	// s->c->arg = ft_malloc(s->c->arg, sizeof(char **) * 4);
	// s->c->arg[0] = s->c->command;
	// s->c->arg[1] = NULL;
	// s->c->arg[2] = NULL;
	// s->c->arg[3] = NULL; 
	// s->c->isfollowedbypipe = 1;
	// s->c->isprecededbypipe = 0;
	// s->c->nextpipe = &test;

// //test with 1
	// s->pipe = 1;	
	// s->c->line = "grep make";
	// s->c->nbarg = 1;
	// s->c->command = "grep";
	// s->c->arg = ft_malloc(s->c->arg, sizeof(char **) * 4);
	// s->c->arg[0] = s->c->command;
	// s->c->arg[1] = "make";
	// s->c->arg[2] = NULL;
	// s->c->arg[3] = NULL; 
	// s->c->isfollowedbypipe = 2;
	// s->c->isoutfile = 0;
	// s->c->isinputfile = 1;
	// s->c->outfile = NULL;
	// s->c->inputfile = "Makefile";
	// s->c->isprecededbypipe = 0;
	// s->c->nextpipe = NULL;

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
	// t_mother *tmp;
	// // int ret = 0;
	// int i = 0;
	// while(i < 1)
	// {
	// 	tmp = s;
	// 	// puts("ZGEG");
	// 	ft_pipe(s->c, tmp);
	// 	if(!s->c->nextpipe)
	// 		break;
	// 	s->c = s->c->nextpipe;
	// 	i++;
	// }

		t_mother *tmp;
	// int ret = 0;
	int i = 0;
	printf("\n|||| %d |||||\n", s->nbcmd);
	while(i < s->nbcmd)
	{
		tmp = s;
		// puts("ZGEG");
		ft_pipe(s->c, tmp);
		if(!s->c->nextpipe)
			break;
		s->c = s->c->nextpipe;
		i++;
	}
	mainaftersignal();
	// printf("||hello");
}