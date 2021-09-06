/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 16:31:30 by ogenser           #+#    #+#             */
/*   Updated: 2021/09/06 18:53:43 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_initc(t_mother *s)
{
	t_command	c;

	c.line = NULL;
	c.command = "ls";
	c.retvalue = 0;
	c.nbarg = 0;
	c.arg = NULL;
	c.isfollowedbypipe = 0;
	c.nextpipe = 0;
	c.isprecededbypipe = 0;
	c.previouspipe = NULL;
	c.isinputfile = 0;
	c.outfile = NULL;
	c.isinputfile = 0;
	c.inputfile = 0;
	c.iserrofile = 0;
	c.errorfile = NULL;
	s->c = &c;
	// return(&c);
}

void	ft_structinit(t_mother *s)
{
	s->line = NULL;
	s->nbcmd = 0;
	s->pipe = 0;
	s->exitret = 0;
	s->path = NULL;
	ft_initc(s);
}

void	ft_end(t_mother *s)
{
	if (s->line)
		free(s->line);
	// if (s->c)
	// 	free(s->c);
	exit(0);
}