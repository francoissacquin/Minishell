/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 20:16:52 by ogenser           #+#    #+#             */
/*   Updated: 2021/10/02 18:32:32 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	sighandl(void)
{
	// int pid = getpid();
	// printf("HELLO");
	// 	printf("jhgj PID=%d, kajhakjh\n", pid);

	// kill(SIGUSR1, pid);
	write(1, "\n", 1);
	
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	// TUER LES ENFANTS ICI
}

void	quithandler(void)
{
	//printf("g_pid = %i\n", g_pid.pid);
	if (g_pid.pid != 0)
	{
		kill(g_pid.pid, SIGQUIT);
		write(1, "Minishell quit, core dumped\n", 28);
	}
}

void	signalhandler(int c)
{
	//printf("|%d|", c);
	// signal(SIGINT, SIG_DFL);
	// if (c == SIGQUIT)
	// {
	// 	printf("va falloir gerer le ctrl-\\ mieux que ca\n");
	// 	printf("^\\Quit: (core dumped)\n"); //dois on vraiment faire un core dump?
	// 	sighandl();
	// 	return;
	// 	// mainaftersignal();
	if (c == SIGQUIT)
	{
		write(1, "\b\b  \b\b", 6);
		quithandler();
		return;
	}
	else if (c == SIGINT)
	{
		//printf("\n");
		// signal(SIGINT, signalhandler);
		write(1, "\b\b  ", 4);
		// return;
		sighandl();
		// write(1,"\nMinishellS> ", 14);
		// rl_redisplay();
		// write(1,"\b", 1);
		//mainaftersignal();
		return ;
	}
	// signal(SIGINT, SIG_DFL);
}
