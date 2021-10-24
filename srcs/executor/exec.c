/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 11:00:09 by ogenser           #+#    #+#             */
/*   Updated: 2021/10/21 20:15:40 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_fileexits(char *testpath)
{
	struct stat	s_buf;
	int			ret;

	ret = -1;
	if (stat(testpath, &s_buf) == 0)
		ret = 0;
	return (ret);
}

char	*ft_pathtester(t_mother *s, char ***minipath, int minisize)
{
	int			i;
	int			j;
	char		*testpath;
	char		*testpath2;
	int			pathsize;
	char		*addcmd;
	int			pathfound;

	(void)s;
	pathfound = -1;
	pathsize = 0;
	i = 0;
	while (i < minisize && pathfound == -1)
	{
		while (minipath[i][pathsize])
			pathsize++;
		testpath = ft_strjoin("", "/");
		j = 0;
		while (j < pathsize && pathfound == -1)
		{
			testpath2 = ft_strjoin(testpath, minipath[i][j]);
			free(testpath);
			testpath = ft_strjoin(testpath2, "/");
			free(testpath2);
			addcmd = ft_strjoin(testpath, s->c->command);
			if (ft_fileexits(addcmd) == 0)
				pathfound = 1;
			j++;
			if (j < pathsize && pathfound == -1)
				free(addcmd);
		}
		free(testpath);
		i++;
		if (i < minisize && pathfound == -1)
			free(addcmd);
		pathsize = 0;
	}
	return (addcmd);
}

char	*ft_pathfinder(t_mother *s)
{
	char		*rightpath;
	char		**path;
	char		***minipath;
	int			i;
	int			minipathsize;

	minipathsize = 0;
	i = 0;
	minipath = NULL;
	path = ft_split(s->path, ':');
	while (path[i])
		i++;
	while (s->path[i])
	{
		if (s->path[i] == ':')
			minipathsize++;
		i++;
	}
	minipathsize++;
	minipath = ft_malloc(&minipath, sizeof(char **) * minipathsize);
	i = 0;
	while (i < minipathsize)
	{
		minipath[i] = ft_split(path[i], '/');
		i++;
	}
	rightpath = ft_pathtester(s, minipath, minipathsize);
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

int	ft_execnotbuiltin(t_mother *s)
{
	int		error;
	char	*path;

	printf("passage par les erreurs\n");
	path = ft_pathfinder(s);
	error = 0;
	error = execve(path, s->c->arg, s->env);
	free(path);
	return (error);
}

int	ft_execfind(t_mother *s, t_command *c)
{
	int	ret;

	ret = 1;
	s->c = c;
	if (ft_strcmp("cd", s->c->command) == 0)
		ret = ft_cd(s);
	else if (ft_strcmp("echo", s->c->command) == 0)
		ret = ft_echo(s, s->c);
	else if (ft_strcmp("env", s->c->command) == 0)
		ret = ft_env(s);
	else if (ft_strcmp("exit", s->c->command) == 0)
		ret = ft_exit(s, c);
	else if (ft_strcmp("export", s->c->command) == 0 && s->c->nbarg == 1)
		ret = ft_export(s, c);
	else if (ft_strcmp("pwd", s->c->command) == 0)
		ret = ft_pwd(s);
	else if (ft_strcmp("unset", s->c->command) == 0)
		ret = ft_unset(s, c);
	else
		ret = ft_execnotbuiltin(s);
	return (ret);
}
