/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 16:27:55 by ogenser           #+#    #+#             */
/*   Updated: 2021/09/08 12:06:18 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// int		ft_fileexits(char *testpath)
// {
// 	struct stat s_buf;
// 	int ret = -1;

// 	if (stat(testpath, &s_buf) == 0)
// 		ret = 0;
// 	return(ret);
// }

// char	*ft_pathtester(t_mother *s, char ***minipath, int minisize)
// {
// 	int i = 0;
// 	int j;
// 	char *testpath;
// 	int pathsize = 0;
// 	char *addcmd;
// 	int	pathfound = -1;

// 	(void)s;
// 	testpath = ft_strjoin(minipath[i][0], "/");
// 	while(i < minisize && pathfound == -1)
// 	{
// 		while (minipath[i][pathsize])
// 			pathsize++;
// 		testpath = ft_strjoin("", "/");
// 		j = 0;
// 		while(j < pathsize && pathfound == -1)
// 		{
// 			testpath = ft_strjoin(testpath, minipath[i][j]);
// 			testpath = ft_strjoin(testpath, "/");
// 			addcmd = ft_strjoin(testpath, "ls"); 
//			//replace by s->c->command after parse
// 			if(ft_fileexits(addcmd) == 0)
// 				pathfound = 1;
// 			j++;
// 		}
// 		i++;
// 		pathsize = 0;
// 	}
// 	//tester pour file at /
// 	printf("||%s\n||", addcmd);
// 	return(addcmd);
// }

// char	*ft_pathfinder(t_mother *s)
// {
// 	char *rightpath;
// 	char **path;
// 	char ***minipath = NULL;
// 	int 	i = 0;
// 	int minipathsize = 0;

// 	path = ft_split(s->path, ':');
// 	while(path[i])
// 		i++;
// 	while (s->path[i])
// 	{
// 		if (s->path[i] == ':')
// 			minipathsize++;
// 		i++;
// 	}
// 	minipathsize++;
// 	// printf("||%d||", minipathsize);
// 	minipath = malloc(sizeof(char **) * minipathsize);
// 	i = 0;
// 	while(i < minipathsize)
// 	{
// 		minipath[i] = ft_split(path[i], '/');
// 		i++;
// 	}
// 	// printf("||%s||||\n", s->c->command);
// 	rightpath = ft_pathtester(s, minipath, minipathsize);
// 	return(rightpath);
// }

// void	ft_execnotbuiltin(t_mother *s)
// {
// 	int	error;
// 	char *path;

// 	path = ft_pathfinder(s);
// 	error = 0;
// 	error = execve(path, s->c->arg, s->env);
// 	// char *test = " -la";
// 	// error = execve(path, &test, NULL); //this is a test
// 	if(error < 0)
// 		ft_error(s, "execve, binary may be corrupted", error);
// }

// void	ft_execfind(t_mother *s)
// {
// 	s->c->command = "l";
// 	//builtins
// 	if (ft_strcmp("cd", s->c->command) == 0)
// 		ft_cd(s);
// 	else if (ft_strcmp("echo", s->c->command) == 0)
// 		ft_echo(s);	
// 	else if (ft_strcmp("env", s->c->command) == 0)
// 		ft_cd(s);
// 	else if (ft_strcmp("exit", s->c->command) == 0)
// 		ft_cd(s);
// 	else if (ft_strcmp("export", s->c->command) == 0)
// 		ft_cd(s);
// 	else if (ft_strcmp("pwd", s->c->command) == 0)
// 		ft_cd(s);
// 	else if (ft_strcmp("unset", s->c->command) == 0)
// 		ft_cd(s);
// 	else
// 		ft_execnotbuiltin(s);
// }

int	ft_parse(t_mother *s)
{
	(void)s;
	return (1);
}
