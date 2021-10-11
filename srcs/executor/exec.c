/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 11:00:09 by ogenser           #+#    #+#             */
/*   Updated: 2021/09/22 19:30:09 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int		ft_fileexits(char *testpath)
{
	struct stat s_buf;
	int ret = -1;

	if (stat(testpath, &s_buf) == 0)
		ret = 0;
	return(ret);
}

char	*ft_pathtester(t_mother *s, char ***minipath, int minisize)
{
	int i = 0;
	int j;
	char *testpath;
	int pathsize = 0;
	char *addcmd;
	int	pathfound = -1;

	(void)s;
	testpath = ft_strjoin(minipath[i][0], "/");
	while(i < minisize && pathfound == -1)
	{
		while (minipath[i][pathsize])
			pathsize++;
		testpath = ft_strjoin("", "/");
		j = 0;
		while(j < pathsize && pathfound == -1)
		{
			testpath = ft_strjoin(testpath, minipath[i][j]);
			testpath = ft_strjoin(testpath, "/");
			addcmd = ft_strjoin(testpath, s->c->command); //replace by s->c->command after parse
			if(ft_fileexits(addcmd) == 0)
				pathfound = 1;
			j++;
		}
		i++;
		pathsize = 0;
	}
	//tester pour file at /
	//printf("||%s\n||", addcmd);
	return(addcmd);
}

char	*ft_pathfinder(t_mother *s)
{
	char *rightpath;
	char **path;
	char ***minipath = NULL;
	int 	i = 0;
	int minipathsize = 0;

	path = ft_split(s->path, ':');
	while(path[i])
		i++;
	while (s->path[i])
	{
		if (s->path[i] == ':')
			minipathsize++;
		i++;
	}
	minipathsize++;
	// printf("||%d||", minipathsize);
	minipath = malloc(sizeof(char **) * minipathsize);
	i = 0;
	while(i < minipathsize)
	{
		minipath[i] = ft_split(path[i], '/');
		i++;
	}
	// printf("||%s||||\n", s->c->command);
	rightpath = ft_pathtester(s, minipath, minipathsize);
	return(rightpath);
}

int	ft_execnotbuiltin(t_mother *s)
{
	int	error;
	char *path;

	path = ft_pathfinder(s);
	error = 0;
	//  printf("%s , %s", path, s->c->arg[0]);
	 //dprintf(1,"fghm");
	error = execve(path, s->c->arg, s->env);
	// char *test = " -la";
	// error = execve(path, &test, NULL); //this is a test
	if(error < 0)
		ft_error(s, "execve, binary may be corrupted", error);
	return(error);
}

int	ft_execfind(t_mother *s, t_command *c)
{
	s->c = c;
	int ret = 1;
	
	//builtins
	if (ft_strcmp("cd", s->c->command) == 0)
		ret = ft_cd(s);
	else if (ft_strcmp("echo", s->c->command) == 0)
		ret = ft_echo(s, s->c);	
	else if (ft_strcmp("env", s->c->command) == 0)
		ret = ft_env(s);
	else if (ft_strcmp("exit", s->c->command) == 0)
		ret = ft_exit(s, c);
	else if (ft_strcmp("export", s->c->command) == 0)
		ret = ft_export(s, c);
	else if (ft_strcmp("pwd", s->c->command) == 0)
		ret = ft_pwd(s);
	else if (ft_strcmp("unset", s->c->command) == 0)
		ret = ft_unset(s, c);
	else
		ret = ft_execnotbuiltin(s);
	return(ret);
}