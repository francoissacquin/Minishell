/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 17:22:46 by ogenser           #+#    #+#             */
/*   Updated: 2021/10/12 17:51:25 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


//cd $home check avec parsing
// cd with deleted . directory //normalement onpeut pas le supp sur linux mais a verifiier chez toi
// replace pwd
// max size of filename is 255 bytes
// cd - et cd ~
//proteger contre trop d arguments

int ft_updatepwd(t_mother *s, char *new_path, char *old_path)
{
	char	*temp;

	temp = ft_strjoin("PWD=", new_path);
	create_env(s, temp);
	free(temp);
	temp = ft_strjoin("OLDPWD=", old_path);
	create_env(s, temp);
	free(temp);
	return (0);
}

int		ft_cd(t_mother *s)
{
	// char *arg = "../minishell/srcs"; //received as argument after parsing
	char *path;
	char *targetpath;
	int		r = 0;
	char *pathhome = NULL;
	char *previouspath = NULL; // a mettre dans la strcuture
	
	path = NULL;
	path = ft_malloc(&path, 400 * sizeof(char));
	targetpath = NULL;
	targetpath = ft_malloc(&targetpath, 400 * sizeof(char));
	ft_memset(path, 0, sizeof(path));
	ft_memset(targetpath, 0, sizeof(targetpath));
	getcwd(path, sizeof(path));
	pathhome = getenv("HOME");
	if (s->c->arg[1] == NULL || ft_strcmp("~", s->c->arg[1]) == 0)
	{
		if (pathhome == NULL)
			ft_error(s, "cd: HOME not set", -1);
		else
		{
			r = chdir(pathhome);
			ft_updatepwd(s, pathhome, path);
		}
		free(path);
		free(targetpath);
		return(0);
	}
	else if (ft_strcmp("-", s->c->arg[1]) == 0)
	{
		previouspath = ft_return_env_value(s, "OLDPWD", 1);
		r = chdir(previouspath);
		//ft_updatepwd();
	}
	else if (ft_strcmp("--", s->c->arg[1]) == 0)
	{
		r = chdir(previouspath);
		previouspath = path;
		//ft_updatepwd();
	}
	else
		r = chdir(s->c->arg[1]); //update oldpwd et pwd ici aussi
	if (r == -1)
	{
		free(path);
		free(targetpath);
		write(2, "bash: line 0: cd: No such file or directory\n", 44);
		return(1);
	}
		//ft_error(s, "chdir failed", -1);
	getcwd(targetpath, sizeof(targetpath));
	ft_updatepwd(s, targetpath, path);
	free(path);
	free(targetpath);
	// ft_pwd(s);
	//printf("%s r = %d", targetpath, r);
	return(0);
}