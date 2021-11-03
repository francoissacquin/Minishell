/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 12:18:17 by ogenser           #+#    #+#             */
/*   Updated: 2021/11/03 21:09:27 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_return(t_command *c, t_mother *s)
{
	int	i;
	int	ex;
	int	ret;
	int	status;

	ret = 0;
	i = 0;
	ex = 0;
	status = 0;
	if (c->nextpipe == NULL)
	{
		while (i < s->nbcmd)
		{
			waitpid(s->pidtab[i], &status, 0);
			if (c->isfollowedbypipe == 0)
			{
				ex = WIFEXITED(status);
				if (ex > -1)
					ret = WEXITSTATUS(status);
			}
			i++;
		}
	}
	return (ret);
}

// on ferme le pipe d'avant : close(c->previouspipe->pipes[0]);
// si suivi ou apres par un pipe on close write side : close(c->pipes[1])
// gestion de la redirection > : (c->isfollowedbyche == 1)
// si c'est le dernier "pipe"
// on branche la sortie du pipe sur stdin pour imprimer : dup2(c->pipes[1], 0);
// si suivi par rien on close le read side : close(c->pipes[0]);
// on attends la fin du child pour etre sur d'avoir tte la sortie 
//: waitpid(pid, &status, 0);
// get return value of child process : ex = WIFEXITED(status);
int	ft_parent(t_command *c, t_mother *s)
{
	int	ret;
	int	fd;

	ret = 0;
	if (c->isprecededbypipe == 1)
		close(c->previouspipe->pipes[0]);
	if (c->isfollowedbypipe == 1 || c->isprecededbypipe == 1)
	{
		close(c->pipes[1]);
		if (c->isfollowedbyche == 1)
			fd = open(c->outfile, O_RDWR | O_CREAT, 0666);
		if (c->nextpipe == NULL)
		{
			dup2(c->pipes[1], 0);
			close(c->pipes[0]);
		}
	}
	ret = ft_return(c, s);
	return (ret);
}

//always fork to save minishell parent in case of crash
// catching signals to kill child processes
//exec child
//exec parent

int	ft_pipe(t_command *c, t_mother *s, int i)
{
	int		err;
	int		ret;
	pid_t	*pid;

	err = 0;
	ret = 1;
	if ((c->isfollowedbypipe <= 1 || c->isprecededbypipe <= 1)
		&& !(c->cmd_status == 1))
		err = pipe(c->pipes);
	else if (((c->isfollowedbypipe == 1 || c->isprecededbypipe == 1)
			&& c->cmd_status == 1))
		err = pipe(c->pipes);
	if (err != 0)
		ft_error(s, "pipe", -1);
	pid = ft_return_global_pid();
	*pid = fork();
	s->pidtab[i] = *pid;
	c->cpid = *pid;
	if (*pid < 0)
		ft_error(s, "fork", -1);
	if (*pid == 0)
		ret = ft_child(c, s);
	else
		ret = ft_parent(c, s);
	return (ret);
}

void	multicommandsbuiltins(t_mother *s, t_command *cmd, int i)
{
	if (ft_strcmp("exit", cmd->command) == 0)
		cmd->retvalue = ft_exit(s, cmd);
	else if (ft_strcmp("cd", cmd->command) == 0)
	{
		if (s->nbcmd > 1)
			ft_pipe(cmd, s, i);
		cmd->retvalue = ft_cd(s);
	}
	else if (ft_strcmp("export", cmd->command) == 0 && cmd->nbarg > 1)
	{
		ft_pipe(cmd, s, i);
		if (cmd->nbarg > 0)
			cmd->retvalue = ft_export(s, cmd);
	}
	else if (ft_strcmp("echo", cmd->command) == 0)
		cmd->retvalue = ft_pipe(cmd, s, i);
	else if (ft_strcmp("unset", cmd->command) == 0)
	{
		ft_pipe(cmd, s, i);
		cmd->retvalue = ft_unset(s, cmd);
	}
	else if (cmd->command == NULL)
		cmd->retvalue = 127;
	else if (!(ft_strcmp("cd", cmd->command) == 0))
		cmd->retvalue = ft_pipe(cmd, s, i);
}

//sends to different functions if its a pipe redirect etc
//finds if it needs to be forked then loop for n commands
//look for if (s->c->command == NULL) 
// pas sur que ca fonctionne // and used twice

void	multicommands(t_mother *s)
{
	int			i;
	pid_t		*pid;
	t_command	*cmd;

	i = 0;
	cmd = s->c;
	if (cmd->command == NULL)
	{
		cmd->retvalue = 127;
		s->ret = cmd->retvalue;
	}
	s->pidtab = ft_malloc(&s->pidtab, (sizeof(pid_t) * s->nbcmd));
	while (i < s->nbcmd)
	{
		multicommandsbuiltins(s, cmd, i);
		s->ret = cmd->retvalue;
		if (!cmd->nextpipe)
			break ;
		cmd = cmd->nextpipe;
		i++;
	}
	free(s->pidtab);
	pid = ft_return_global_pid();
}
