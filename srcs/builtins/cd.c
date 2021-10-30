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
// cd with deleted . directory //normalement on peut pas le supp
// sur linux mais a verifiier chez toi
// replace pwd
// max size of filename is 255 bytes
// cd - et cd ~
//proteger contre trop d arguments

int	ft_updatepwd(t_mother *s, char *new_path, char *old_path)
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

int	ft_cd(t_mother *s)
{
	char	path[1000];
	char	targetpath[1000];
	int		r;
	char	*pathhome;
	char	*previouspath;

	r = 0;
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
		return (0);
	}
	else if (ft_strcmp("-", s->c->arg[1]) == 0)
	{
		previouspath = ft_return_env_value(s, "OLDPWD", 1);
		r = chdir(previouspath);
	}
	else if (ft_strcmp("--", s->c->arg[1]) == 0)
	{
		r = chdir(previouspath);
		previouspath = path;
	}
	else
		r = chdir(s->c->arg[1]);
	if (r == -1)
	{
		write(2, "bash: line 0: cd: No such file or directory\n", 44);
		return (1);
	}
	getcwd(targetpath, sizeof(targetpath));
	if (ft_strcmp("-", s->c->arg[1]) == 0)
		printf("%s\n", targetpath);
	ft_updatepwd(s, targetpath, path);
	return (0);
}
