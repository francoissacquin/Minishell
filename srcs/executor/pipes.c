/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 12:18:17 by ogenser           #+#    #+#             */
/*   Updated: 2021/10/21 20:34:24 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//on branche les redirections
//si y'a un pipe avant on connecte la sortie du pipe au stdin 
//: dup2(c->previouspipe->pipes[0], 0);
// si pipe apres on branche l'entree du pipe sur le stdout 
//: dup2(c->pipes[1], 1);
//execute command in child process meme si il y'en a que une

int	ft_child(t_command *c, t_mother *s)
{
	int	err;
	int	ret;

	err = 0;
	ret = 1;
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

// peut etre a mettre a la fin 
// on ferme le pipe d'avant : close(c->previouspipe->pipes[0]);
// si suivi ou apres par un pipe on close write side : close(c->pipes[1])
// gestion de la redirection > : (c->isfollowedbypipe == 2)
// si c'est le dernier "pipe"
// on branche la sortie du pipe sur stdin pour imprimer : dup2(c->pipes[1], 0);
// si suivi par rien on close le read side : close(c->pipes[0]);
// on attends la fin du child pour etre sur d'avoir tte la sortie 
//: waitpid(pid, &status, 0);
// get return value of child process : ex = WIFEXITED(status);

int	ft_waitpid(t_mother *s, int status)
{
	t_mother	*tmp;
	int			i;
	int 		ex;
	int			ret;

	i = 1;
	tmp = s;
	ex = 0;
	ret = 1;
	while (i < s->nbcmd)
	{
		waitpid(tmp->c->cpid, &status, 0);
		if(tmp->c->isfollowedbypipe == 0)
		{	ex = WIFEXITED(status);
			if (ex > -1)
				ret = WEXITSTATUS(status);
		}
		i++;
			tmp->c = tmp->c->previouspipe;
	}
	return (ret);
}

int		ft_parent(t_command *c, t_mother *s)
{
	int ret;
	int fd;

	ret = 0;
	if (c->isprecededbypipe == 1)
		close(c->previouspipe->pipes[0]);
	if(c->isfollowedbypipe == 1|| c->isprecededbypipe == 1)// || c->isfollowedbypipe == 2)
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
	return(ret);
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

	if(c->isfollowedbypipe <= 1 || c->isprecededbypipe <= 1)
		err = pipe(c->pipes);
	if(err != 0)
		ft_error(s, "pipe", -1);
	pid = ft_return_global_pid();
	*pid = fork();
	c->cpid = *pid;
	if(*pid < 0)
		ft_error(s, "fork", -1);
	// signal(SIGINT, killchild);
	// signal(SIGQUIT, quitchild);
	if(*pid == 0)
		ret = ft_child(c, s);
	else
	{
		ret = ft_parent(c, s);
	}
	int status = 0;
	int ex = 0;
	if(s->c->isfollowedbypipe == 0 && s->nbcmd > 1)
		ret = ft_waitpid(s, status);
	else if (s->nbcmd == 1 || s->c->isfollowedbypipe == 2 || s->c->isfollowedbypipe == 3)
	{
		waitpid(*pid, &status, 0);
		ex = WIFEXITED(status);
		if (ex > 0)
			ret = WEXITSTATUS(status);
	}
	return (ret);
}

//sends to different functions if its a pipe redirect etc
//finds if it needs to be forked then loop for n commands
//look for if (s->c->command == NULL) // pas sur que ca fonctionne // and used twice

void		multicommands(t_mother *s)
{	
	t_mother	*tmp;
	int			i;
	pid_t		*pid;
	
	i = 0;
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
		}
		else if (ft_strcmp("export", s->c->command) == 0 && s->c->nbarg > 1)
		{
			ft_pipe(s->c, s);
			if (s->c->nbarg > 0)
			{
			s->c->retvalue = ft_export(s, s->c);
			}
		}
		else if (ft_strcmp("echo", s->c->command) == 0)
		{
			s->c->retvalue =ft_pipe(s->c, s);
		}
		else if (ft_strcmp("unset", s->c->command) == 0)
		{
			ft_pipe(s->c, s);
			s->c->retvalue = ft_unset(s, s->c);
		}
		else if (s->c->command == NULL)
			s->c->retvalue = 127;
		else if (!(ft_strcmp("cd", s->c->command) == 0))
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
