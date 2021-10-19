/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 12:18:17 by ogenser           #+#    #+#             */
/*   Updated: 2021/10/19 14:25:26 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//check les flags d'open
//gestion, branchement de > et >> : c->isfollowedbypipe == 2 || c->isfollowedbypipe == 3
//gestion redirection < et << : c->isprecededbypipe == 2 || c->isprecededbypipe == 3
//connect read side to stdin : dup2(fd, 0);
//fermeture du fd

// int		ft_redirect(t_command *c, t_mother *s)
// {
// 	int	err;
// 	int	fd;

// 	err = 0;
// 	fd = 0;
// 	if (c->isfollowedbypipe == 2)
// 		fd = open(c->outfile, O_RDWR|O_CREAT, 0666);
// 	if (c->isfollowedbypipe == 3)
// 		fd = open(c->outfile, O_RDWR|O_APPEND|O_CREAT, 0666);
// 	if (c->isfollowedbypipe == 2 || c->isfollowedbypipe == 3)
// 		err = dup2(fd, 1);
// 	if (err < 0)
// 		ft_error(s, "redirect dup2", -1);
// 	if (c->isfollowedbypipe == 2 || c->isfollowedbypipe == 3)
// 		err = dup2(fd, 2);
// 	if (err < 0)
// 		ft_error(s, "redirect dup2", -1);
// 	if (c->isprecededbypipe == 2 || c->isprecededbypipe == 3)
// 	{
// 		fd = open(c->inputfile, O_RDWR|O_APPEND, 0666);
// 		err = dup2(fd, 0);
// 		close(c->pipes[1]);
// 		if (err < 0)
// 			ft_error(s, "pipe dup2", -1);
// 		if (c->isprecededbypipe == 3)
// 			unlink(c->inputfile);
// 		close(fd);
// 	}
// 	if(fd)
// 		close(fd);
// 	return(err);
// }

//on branche les redirections
//si y'a un pipe avant on connecte la sortie du pipe au stdin : dup2(c->previouspipe->pipes[0], 0);
// si pipe apres on branche l'entree du pipe sur le stdout : dup2(c->pipes[1], 1);
//execute command in child process meme si il y'en a que une

int		ft_child(t_command *c, t_mother *s)
{
	int err = 0;
	int ret = 1;

	if (c->isfollowedbypipe > 1 || c->isprecededbypipe == 2  || c->isprecededbypipe == 3)
		err = ft_redirect(c, s);
	if (c->isprecededbypipe == 1)
	{
		err = dup2(c->previouspipe->pipes[0], 0);
		if (err < 0)
			ft_error(s, "pipe iii dup2", -1);
	}
	if (c->isfollowedbypipe == 1)
	{
		err = dup2(c->pipes[1], 1);
		if (err < 0)
			ft_error(s, "pipe in grep dup2", -1);
	}
	ret = ft_execfind(s, s->c);
	exit(ret);
}

// peut etre a mettre a la fin // on ferme le pipe d'avant : close(c->previouspipe->pipes[0]);
// si suivi ou apres par un pipe on close write side : close(c->pipes[1])
// gestion de la redirection > : (c->isfollowedbypipe == 2)
// si c'est le dernier "pipe"
// on branche la sortie du pipe sur stdin pour imprimer : dup2(c->pipes[1], 0);
// si suivi par rien on close le read side : close(c->pipes[0]);
// on attends la fin du child pour etre sur d'avoir tte la sortie : waitpid(pid, &status, 0);
// get return value of child process : ex = WIFEXITED(status);

int		ft_parent(t_command *c, int *pid)
{
	t_mother *tmp;
	int i = 0;

	tmp = s;
	while (i < s->nbcmd)
	{
		printf("%d\n", tmp->c->cpid);
		waitpid(tmp->c->cpid, &status, 0);
		if(i < s->nbcmd - 1)
			tmp->c = tmp->c->previouspipe;
		i++;
	}
	
}

int		ft_parent(t_command *c, t_mother *s)
{
	int status = 0;
	int ret = 1;
	int ex = 0;
	int fd;

	if (c->isprecededbypipe == 1)
		close(c->previouspipe->pipes[0]);
	if(c->isfollowedbypipe == 1|| c->isprecededbypipe == 1 || c->isfollowedbypipe == 2)
	{
		close(c->pipes[1]);
		if (c->isfollowedbypipe == 2)
			fd = open(c->outfile, O_RDWR|O_CREAT, 0666);
		if (c->nextpipe == NULL)
		{
			dup2(c->pipes[1], 0);
			close(c->pipes[0]);
		}
	}
	waitpid(*pid, &status, 0);
	ex = WIFEXITED(status);
	if (ex > 0)
		ret = WEXITSTATUS(status);
	return(ret);
}

//ctrl-c handler in child process //move to signals

void	killchild(int signal)
{
	pid_t	*pid;

	(void)signal;
	pid = ft_return_global_pid();
	kill(*pid, SIGTERM);
}

//ctrl-\ handler in child process

void	quitchild(int signal)
{
	pid_t	*pid;

	(void)signal;
	pid = ft_return_global_pid();
	if (*pid != -1)
		kill(*pid, SIGTERM);
}

//always fork to save minishell parent in case of crash
// catching signals to kill child processes
//exec child
//exec parent

int		ft_pipe(t_command *c, t_mother *s)
{
	int err = 0;
	int ret = 1;
	pid_t	*pid;

	if(c->isfollowedbypipe == 1 || c->isprecededbypipe == 1)
		err = pipe(c->pipes);
	if(err != 0)
		ft_error(s, "pipe", -1);
	pid = ft_return_global_pid();
	*pid = fork();
	if(*pid < 0)
		ft_error(s, "fork", -1);
	// signal(SIGINT, killchild);
	// signal(SIGQUIT, quitchild);
	if(*pid == 0)
		ret = ft_child(c, s);
	else
		ret = ft_parent(c, pid);
	return(ret);
}


int		ft_exec_builtins(t_command *c, t_mother *s)
{
	int ret = 1;
	int	err = 0;
	int fd = 0;

	// write(1, "hello", 5);
	if(c->isfollowedbypipe == 1 || c->isprecededbypipe == 1)
		err = pipe(c->pipes);
	// if(err != 0)
	// 	ft_error(s, "pipe", -1);
	// ret = ft_redirect(c, s);
	// write(1, "cacao", 5);
	// // if (c->isprecededbypipe == 1)
	// // {
	// // 	err = dup2(c->previouspipe->pipes[0], 0);
	// // 	if (err < 0)
	// // 		ft_error(s, "pipe dup2", -1);
	// // }
	// if (c->isfollowedbypipe == 1)
	// {
	// 	err = dup2(c->pipes[1], 1);
	// 	if (err < 0)
	// 		ft_error(s, "pipe dup2", -1);
	// 	// err = dup2(c->pipes[1], 0);
	// 	// if (err < 0)
	// 	// 	ft_error(s, "pipe dup2", -1);
	// }
	// ft_export(s, c);
	// if (c->isprecededbypipe == 1)
	// 	close(c->previouspipe->pipes[0]);
	// if(c->isfollowedbypipe == 1 || c->isprecededbypipe == 1 || c->isfollowedbypipe == 2)
	// {
	// 	// if(c->nextpipe == NULL)
	// 	close(c->pipes[1]);
	// 	if (c->isfollowedbypipe == 2)
	// 		fd = open(c->outfile, O_RDWR|O_CREAT, 0666);
	// 	if (c->nextpipe == NULL)
	// 	{
	// 		dup2(c->pipes[1], 0);
	// 		close(c->pipes[0]);
	// 	}
	// }
	// if(fd)
	// 	close(fd);
	// dup2(c->pipes[1], 0);
	// ft_export(s, c);
	//write(2, "hello", 5);
	// if (c->isfollowedbypipe > 1 || c->isprecededbypipe == 2  || c->isprecededbypipe == 3)
	// 	err = ft_redirect(c, s);
	if (c->isprecededbypipe == 1)
	{
		err = dup2(c->previouspipe->pipes[0], 0);
		if (err < 0)
			ft_error(s, "pipe dup2", -1);
	}
	fd = open("hello.txt", O_RDWR|O_CREAT, 0666);
	//write(fd, "chips", 5);
	if (c->isfollowedbypipe == 1)
	{
		err = dup2(c->pipes[1], 1);
		if (err < 0)
			ft_error(s, "pipebuilt dup2", -1);
	}
	ft_export(s, c);
	// close(1);
	if (c->isprecededbypipe == 1)
		close(c->previouspipe->pipes[0]);
	if(c->isfollowedbypipe == 1|| c->isprecededbypipe == 1 || c->isfollowedbypipe == 2)
	{
		close(c->pipes[1]);
		if (c->isfollowedbypipe == 2)
			fd = open(c->outfile, O_RDWR|O_CREAT, 0666);
		if (c->nextpipe == NULL)
		{
			dup2(c->pipes[1], 0);
			close(c->pipes[0]);
		}
	}
	// ft_export(s, c);
	return(ret);
}


int		ft_routeenv(t_mother *s, t_command *c)
{
		int ret = 1;
	int	err = 0;
	int fd = 0;

	// write(1, "hello", 5);
	if(c->isfollowedbypipe == 1 || c->isprecededbypipe == 1)
		err = pipe(c->pipes);
	// if (c->isprecededbypipe == 1)
	// {
	// 	err = dup2(c->previouspipe->pipes[0], 0);
	// 	if (err < 0)
	// 		ft_error(s, "pipe dup2", -1);
	// }
	fd = open("hello.txt", O_RDWR|O_CREAT, 0666);
	//write(fd, "chips", 5);
	if (c->isfollowedbypipe == 1)
	{
		err = dup2(c->pipes[1], 1);
		if (err < 0)
			ft_error(s, "pipebuilt dup2", -1);
	}
	ft_env(s);
	// close(1);
	if (c->isprecededbypipe == 1)
		close(c->previouspipe->pipes[0]);
	if(c->isfollowedbypipe == 1|| c->isprecededbypipe == 1 || c->isfollowedbypipe == 2)
	{
		close(c->pipes[1]);
		if (c->isfollowedbypipe == 2)
			fd = open(c->outfile, O_RDWR|O_CREAT, 0666);
		if (c->nextpipe == NULL)
		{
			dup2(c->pipes[1], 0);
			close(c->pipes[0]);
		}
	}
	// ft_export(s, c);
	return(ret);
}

//sends to different functions if its a pipe redirect etc
//finds if it needs to be forked then loop for n commands
//look for if (s->c->command == NULL) // pas sur que ca fonctionne // and used twice

void		multicommands(t_mother *s)
{	
	t_mother *tmp;
	int i = 0;
	pid_t	*pid;
	
	if (s->c->command == NULL)
	{
		s->c->retvalue = 127;
		s->ret = s->c->retvalue;
	}
	while(i < s->nbcmd)
	{
		tmp = s;
		if (ft_strcmp("exit", s->c->command) == 0)
			s->c->retvalue = ft_exit(s, s->c);
		else if (ft_strcmp("cd", s->c->command) == 0)
		{
			ft_pipe(s->c, s);
			s->c->retvalue = ft_cd(s);
			//s->c->nextpipe = 0; //c'est tres douteux mais ca a l'air de marcher
		}
		else if (ft_strcmp("export", s->c->command) == 0 && s->c->nbarg > 1)
		{// ft_exec_builtins(s->c, s);
			//printf("||%d|", s->c->nbarg);
			ft_pipe(s->c, s);
			if (s->c->nbarg > 0)
			{
			s->c->retvalue = ft_export(s, s->c);
			//s->c->nextpipe = 0;
			//puts("export\n");
			}
		}
		// else if (ft_strcmp("env", s->c->command) == 0)
		// {// ft_exec_builtins(s->c, s);
		// 	puts("ENV\n");
		// 	if (s->c->isfollowedbypipe == 1)
		// 		ft_routeenv(s, s->c);
		// 	else
		// 		s->c->retvalue = ft_env(s);
		// //	s->c->nextpipe = 0;
		// }
		else if (ft_strcmp("unset", s->c->command) == 0)
		{
			//puts("UNSET\n");
			ft_pipe(s->c, s);
			s->c->retvalue = ft_unset(s, s->c);
		}
		else if (s->c->command == NULL)
			s->c->retvalue = 127;
		else if (!(ft_strcmp("cd", s->c->command) == 0) /*&& !(ft_strcmp("export", s->c->command) == 0)*/)
			s->c->retvalue = ft_pipe(s->c, tmp);
		s->ret = s->c->retvalue;
		if(!s->c->nextpipe)
			break; 
		s->c = s->c->nextpipe;
		i++;
	}
	pid = ft_return_global_pid();
	*pid = 0;
}