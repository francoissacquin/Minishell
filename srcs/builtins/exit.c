/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 17:22:56 by ogenser           #+#    #+#             */
/*   Updated: 2021/10/04 16:21:47 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//missing 
//find how to make the return of a command to a number
// export to superior level of shell so it's accessible after being exited with echo $?

int ft_exit(t_mother *s)
{
	// if (s->c->isprecededbypipe != 0 && s->c->isfollowedbypipe == 0)
	// {
	// 	signal(SIGINT, signalhandler);
	// }
	// else if(s->c->isprecededbypipe != 0 && s->c->isfollowedbypipe != 0)
	// {
	// 	s->c = s->c->nextpipe;
	// 	multicommands(s);
	// }
			printf("PPPPs->ret %dPPPP s->c->retvalue %d PPPP\n", s->ret, s->c->retvalue);


	printf("PPPP%dPPPP\n", s->ret);
	puts("CACACACACACAC");
	write(2, "exit\n", 5);
	ft_end(s);
	// s->ret = 234;
	exit(s->ret);
}
