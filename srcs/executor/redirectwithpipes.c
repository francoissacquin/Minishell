/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 12:18:22 by ogenser           #+#    #+#             */
/*   Updated: 2021/10/21 20:18:08 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//works in chiild process
//check les flags d'open
//gestion, branchement de > et >> : c->isfollowedbypipe == 2 
//|| c->isfollowedbypipe == 3
//gestion redirection < et << : c->isprecededbypipe == 2 
//|| c->isprecededbypipe == 3
//connect read side to stdin : dup2(fd, 0);
//fermeture du fd

int	ft_redirect(t_command *c, t_mother *s)
{
	int	err;
	int	fd;

	err = 0;
	fd = 0;
	if (c->isfollowedbypipe == 2)
		fd = open(c->outfile, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (c->isfollowedbypipe == 3)
		fd = open(c->outfile, O_RDWR | O_APPEND | O_CREAT, 0666);
	if (c->isfollowedbypipe == 2 || c->isfollowedbypipe == 3)
		err = dup2(fd, 1);
	if (err < 0)
		ft_error(s, "redirect dup2", -1);
	if (c->isfollowedbypipe == 2 || c->isfollowedbypipe == 3)
		err = dup2(fd, 2);
	if (err < 0)
		ft_error(s, "redirect dup2", -1);
	if (c->isprecededbypipe == 2 || c->isprecededbypipe == 3)
	{
		fd = open(c->inputfile, O_RDWR | O_APPEND, 0666);
		err = dup2(fd, 0);
		close(c->pipes[1]);
		if (err < 0)
			ft_error(s, "pipe dup2", -1);
		if (c->isprecededbypipe == 3)
			unlink(c->inputfile);
		close(fd);
	}
	if (fd)
		close(fd);
	return (err);
}
