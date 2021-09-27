/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 20:16:52 by ogenser           #+#    #+#             */
/*   Updated: 2021/09/27 19:06:46 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	signalhandler(int c)
{
	//printf("|%d|", c);
	// signal(SIGINT, SIG_DFL);
	if (c == SIGQUIT)
	{
		printf("va falloir gerer le ctrl-\\ mieux que ca\n");
		printf("^\\Quit: 3\n");
		mainaftersignal();
	}
	if (c == SIGINT)
	{
		//printf("\n");
		signal(SIGINT, signalhandler);
		write(1,"\nMinishellS> ", 14);
		// write(1,"\b", 1);
		//mainaftersignal();
		return ;
	}
	// signal(SIGINT, SIG_DFL);
}

