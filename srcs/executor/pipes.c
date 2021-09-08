/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 12:18:17 by ogenser           #+#    #+#             */
/*   Updated: 2021/09/08 16:37:04 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_pipe(t_mother *s)
{
	printf("hello");
	printf("hello%s\n", s->c->nextpipe->line);
}

void		multicommands(t_mother *s) 	//sends to different functions if its a pipe redirect etc
{	
	//testing:
	t_command *test = NULL;

printf("hello");
test = (t_command *)ft_malloc(test, sizeof(test) * 1000);
test->line = "grep pipe";
// test->command = ft_strdup("grep");
test->retvalue = 0;
test->nbarg = 1;
test->arg = ft_malloc(test->arg, (sizeof(char *) * 10));
test->arg[0] = ft_malloc(&test->arg[0], (sizeof(char) * 10));
test->arg[0] = "pipes.c";
test->isfollowedbypipe = 0;
test->nextpipe = NULL;
test->isprecededbypipe = 1;
// test->previouspipe = s->c;

char *caca = ("cat pipes.c");
(void)caca;
s->c->line = caca;//ft_strjoin("", "cat pipes.c");
s->c->command = "cat";
s->c->retvalue = 1;
s->c->nbarg = 1;
s->c->arg = ft_malloc(&s->c->arg, (sizeof(char *) * 10));
s->c->arg[0] = ft_malloc(&s->c->arg[0], (sizeof(char) * 10));
s->c->arg[0] = "pipes.c";
s->c->isfollowedbypipe = 1;
s->c->nextpipe = NULL;//&test;
s->c->isprecededbypipe = 0;

// s->c->previouspipe = 0;
// s->c->isoutfile = 0; //boo
// s->c->outfile = 0;  //pat
// s->c->isinputfile = 0; //b
// s->c->inputfile = 0;  //p
// s->c->iserrofile = 0; //ch
// s->c->errorfile = 0;
	// if(s->c->isfollowedbypipe == 1)
	// 	ft_pipe(s);
	// if(s->c->isfollowedbypipe == 2)
	// 	ft_redirect(s);
	printf("||hello");
}