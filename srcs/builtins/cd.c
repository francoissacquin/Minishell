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
	int		r;
	char	*pathhome;

	pathhome = NULL;
	if (ft_strlen_array(s->c->arg) > 2)
	{
		write(2, "Minishell : cd too many argument\n", 33);
		return (1);
	}
	ft_cd_init(s, &pathhome);
	if (s->c->arg[1] == NULL || ft_strcmp("~", s->c->arg[1]) == 0)
	{
		r = ft_cd_conveyor_belt(s, pathhome, 1);
		ft_free_array(s->cd_mem);
		return (0);
	}
	else if (ft_strcmp("-", s->c->arg[1]) == 0)
		r = ft_cd_conveyor_belt(s, pathhome, 2);
	else if (ft_strcmp("--", s->c->arg[1]) == 0)
		r = ft_cd_conveyor_belt(s, pathhome, 3);
	else
		r = chdir(s->c->arg[1]);
	if (r == -1)
	{
		write(2, "bash: line 0: cd: No such file or directory\n", 44);
		ft_free_array(s->cd_mem);
		return (1);
	}
	ft_update_cd(s);
	return (0);
}

void	ft_cd_init(t_mother *s, char **pathhome)
{
	s->cd_mem = ft_malloc(&s->cd_mem, 3 * sizeof(char *));
	s->cd_mem[0] = ft_malloc(&s->cd_mem[0], 1000 * sizeof(char));
	ft_memset(s->cd_mem[0], 0, 1000 * sizeof(char));
	s->cd_mem[1] = ft_malloc(&s->cd_mem[1], 1000 * sizeof(char));
	ft_memset(s->cd_mem[1], 0, 1000 * sizeof(char));
	s->cd_mem[2] = NULL;
	getcwd(s->cd_mem[0], 1000 * sizeof(char));
	*pathhome = getenv("HOME");
}

void	ft_update_cd(t_mother *s)
{
	getcwd(s->cd_mem[1], 1000 * sizeof(char));
	if (ft_strcmp("-", s->c->arg[1]) == 0)
		printf("%s\n", s->cd_mem[1]);
	ft_updatepwd(s, s->cd_mem[1], s->cd_mem[0]);
	ft_free_array(s->cd_mem);
}

int	ft_cd_conveyor_belt(t_mother *s, char *pathhome, int i)
{
	char	*previouspath;
	int		r;

	r = 0;
	if (i == 1)
	{
		if (pathhome == NULL)
			ft_error(s, "cd: HOME not set", -1);
		else
		{
			r = chdir(pathhome);
			ft_updatepwd(s, pathhome, s->cd_mem[0]);
		}
	}
	else if (i == 2)
	{
		previouspath = ft_return_env_value(s, "OLDPWD", 1);
		r = chdir(previouspath);
	}
	else if (i == 3)
	{
		r = chdir(previouspath);
		previouspath = s->cd_mem[0];
	}
	return (r);
}
