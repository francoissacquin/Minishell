/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 12:18:22 by ogenser           #+#    #+#             */
/*   Updated: 2021/10/28 16:07:11 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//works in chiild process
//check les flags d'open
//gestion, branchement de > et >> : c->isfollowedbyche == 1 
//|| c->isfollowedbydoubleche == 1
//gestion redirection < et << : c->isprecededbyche == 2 
//|| c->isprecededbydoubleche == 2
//connect read side to stdin : dup2(fd, 0);
//fermeture du fd

void	ft_redirectfrom(t_command *c, t_mother *s, int fd)
{
	int	err;

	err = 0;
	fd = open(c->inputfile, O_RDWR | O_APPEND, 0666);
	err = dup2(fd, 0);
	if (!(c->isfollowedbypipe))
		close(c->pipes[1]);
	if (err < 0)
		ft_error(s, "pipe dup2", -1);
	if (c->isprecededbydoubleche == 1)
		unlink(c->inputfile);
	close(fd);
}

int	ft_redirect(t_command *c, t_mother *s)
{
	int	err;
	int	fd;

	err = 0;
	fd = 0;
	if (c->isfollowedbyche == 1)
		fd = open(c->outfile, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (c->isfollowedbydoubleche == 1)
		fd = open(c->outfile, O_RDWR | O_APPEND | O_CREAT, 0666);
	if (c->isfollowedbyche == 1 || c->isfollowedbydoubleche == 1)
		err = dup2(fd, 1);
	if (err < 0)
		ft_error(s, "redirect dup2", -1);
	if (c->isfollowedbyche == 1 || c->isfollowedbydoubleche == 1)
		err = dup2(fd, 2);
	if (err < 0)
		ft_error(s, "redirect dup2", -1);
	if (c->isprecededbyche == 1 || c->isprecededbydoubleche == 1)
		ft_redirectfrom(c, s, fd);
	if (fd)
		close(fd);
	return (err);
}

//on branche les redirections
//si y'a un pipe avant on connecte la sortie du pipe au stdin 
//: dup2(c->previouspipe->pipes[0], 0);
// si pipe apres on branche l'entree du pipe sur le stdout 
//: dup2(c->pipes[1], 1);
//execute command in child process meme si il y'en a que une

// #define REDIR (c->isfollowedbyche == 1 
//|| c->isfollowedbydoubleche == 1
// || c->isprecededbyche == 1  || c->isprecededbydoubleche == 1)
// #define REDIRBEFORE (c->isprecededbyche == 1  
//|| c->isprecededbydoubleche == 1)
// #define REDIRAFTER (c->isfollowedbyche == 1 
//|| c->isfollowedbydoubleche == 1)

void	ft_childnorm(t_command *c, t_mother *s)
{
	int	err;

	err = 0;
	if (s->c->isprecededbydoubleche)
		err = ft_redirect(c, s);
	if (c->isfollowedbypipe == 1)
	{
		err = dup2(c->pipes[1], 1);
		close(c->pipes[1]);
		close(c->pipes[0]);
		if (err < 0)
			ft_error(s, "pipe in grep dup2", -1);
	}
}

int	ft_child(t_command *c, t_mother *s)
{
	int	err;
	int	ret;

	err = 0;
	ret = 1;
	if (c->isfollowedbyche == 1 || c->isfollowedbydoubleche == 1
		|| c->isprecededbyche == 1)
		err = ft_redirect(c, s);
	if (c->isprecededbypipe == 1 && !(c->isprecededbyche == 1
			|| c->isprecededbydoubleche == 1))
	{
		err = dup2(c->previouspipe->pipes[0], 0);
		if (err < 0)
			ft_error(s, "pipe iii dup2", -1);
	}
	if ((c->isfollowedbyche == 1 || c->isfollowedbydoubleche == 1))
		ret = ft_execfind(s, c);
	if ((c->isfollowedbyche == 1
			|| c->isfollowedbydoubleche == 1) && !(c->isfollowedbypipe == 1))
		exit(ret);
	ft_childnorm(c, s);
	if (!(c->isfollowedbyche == 1 || c->isfollowedbydoubleche == 1))
		ret = ft_execfind(s, c);
	exit(ret);
}

int	ft_waitpid(t_mother *s, t_command *c, int status)
{
	t_mother	*tmp;
	int			i;
	int			ex;
	int			ret;

	i = 1;
	tmp = s;
	ex = 0;
	ret = 1;
	while (i < s->nbcmd)
	{
		waitpid(c->cpid, &status, 0);
		if (c->isfollowedbypipe == 0)
		{
			ex = WIFEXITED(status);
			if (ex > -1)
				ret = WEXITSTATUS(status);
		}
		i++;
	}
	return (ret);
}
