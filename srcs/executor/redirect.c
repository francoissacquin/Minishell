/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 12:18:22 by ogenser           #+#    #+#             */
/*   Updated: 2021/10/22 23:48:17 by ogenser          ###   ########.fr       */
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
	{
		fd = open(c->inputfile, O_RDWR | O_APPEND, 0666);
		err = dup2(fd, 0);
		if(!(c->isfollowedbypipe))
			close(c->pipes[1]);
		if (err < 0)
			ft_error(s, "pipe dup2", -1);
		if (c->isprecededbydoubleche == 1)
			unlink(c->inputfile);
		close(fd);
	}
	if (fd)
		close(fd);
	return (err);
}
