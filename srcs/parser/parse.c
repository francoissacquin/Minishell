/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 16:27:55 by ogenser           #+#    #+#             */
/*   Updated: 2021/09/06 11:52:08 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_pathfinder(t_mother *s)
{
	char *path = "/bin/";
	(void)s;

	//split env path and test for each with open if path to command is right
	return(path);
}

void	ft_execnotbuiltin(t_mother *s)
{
	int	error;
	char *path;

	s->c->command = "ls";
	s->c->arg[0] = "-la";

	path = ft_pathfinder(s);
	error = 0;
	error = execve(path, s->c->arg, NULL); //third argument must be env
	if(error < 0)
		ft_error(s, "execve", error);
}

void	ft_execfind(t_mother *s)
{
	//builtins
	if (ft_strcmp("cd", s->c->command) == 0)
		ft_cd(s);
	else if (ft_strcmp("echo", s->c->command) == 0)
		ft_echo(s);	
	else if (ft_strcmp("env", s->c->command) == 0)
		ft_cd(s);
	else if (ft_strcmp("exit", s->c->command) == 0)
		ft_cd(s);
	else if (ft_strcmp("export", s->c->command) == 0)
		ft_cd(s);
	else if (ft_strcmp("pwd", s->c->command) == 0)
		ft_cd(s);
	else if (ft_strcmp("unset", s->c->command) == 0)
		ft_cd(s);
	else
		ft_execnotbuiltin(s);
}

int	ft_parse(t_mother *s)
{
	(void)s;
	return(1);
}