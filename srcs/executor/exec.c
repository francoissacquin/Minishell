/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 11:00:09 by ogenser           #+#    #+#             */
/*   Updated: 2021/10/28 17:56:05 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_pathfinder2(t_mother *s, char **path)
{
	char		***minipath;
	int			i;
	int			minipathsize;

	minipathsize = 0;
	i = 0;
	minipath = NULL;
	while (path[i])
		i++;
	while (s->path[i])
	{
		if (s->path[i] == ':')
			minipathsize++;
		i++;
	}
	minipathsize++;
	return (minipathsize);
}

char	*ft_pathfinder(t_mother *s, t_command *c)
{
	char		*rightpath;
	char		**path;
	char		***minipath;
	int			i;
	int			minipathsize;

	path = ft_split(s->path, ':');
	minipathsize = ft_pathfinder2(s, path);
	minipath = ft_malloc(&minipath, sizeof(char **) * minipathsize);
	i = 0;
	while (i < minipathsize)
	{
		minipath[i] = ft_split(path[i], '/');
		i++;
	}
	rightpath = ft_pathtester(c, minipath, minipathsize);
	i = 0;
	while (i < minipathsize)
	{
		ft_free_array(minipath[i]);
		i++;
	}
	free(minipath);
	ft_free_array(path);
	return (rightpath);
}

int	ft_execnotbuiltin(t_mother *s, t_command *c)
{
	int		error;
	char	*path;

	if (c->cmd_status == 3)
		path = c->command;
	else
		path = ft_pathfinder(s, c);
	error = 0;
	error = execve(path, c->arg, s->env);
	free(path);
	return (error);
}

int	ft_execfind(t_mother *s, t_command *c)
{
	int	ret;

	ret = 1;
	if (ft_strcmp("cd", c->command) == 0)
		ret = ft_cd(s);
	else if (ft_strcmp("echo", c->command) == 0)
		ret = ft_echo(s, c);
	else if (ft_strcmp("env", c->command) == 0)
		ret = ft_env(s);
	else if (ft_strcmp("exit", c->command) == 0)
		ret = ft_exit(s, c);
	else if (ft_strcmp("export", c->command) == 0 && s->c->nbarg == 1)
		ret = ft_export(s, c);
	else if (ft_strcmp("pwd", c->command) == 0)
		ret = ft_pwd(s);
	else if (ft_strcmp("unset", c->command) == 0)
		ret = ft_unset(s, c);
	else
		ret = ft_execnotbuiltin(s, c);
	return (ret);
}
