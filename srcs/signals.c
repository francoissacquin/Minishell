/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 20:16:52 by ogenser           #+#    #+#             */
/*   Updated: 2021/10/21 20:36:10 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// TUER LES ENFANTS ICI
void	sighandl(void)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	quithandler(void)
{
	pid_t	*pid;

	pid = ft_return_global_pid();
	if (*pid != 0)
	{
		kill(*pid, SIGQUIT);
		write(1, "Minishell quit, core dumped\n", 28);
		*pid = -1;
	}
}

void	signalhandler(int c)
{
	if (c == SIGQUIT)
	{
		write(1, "\b\b  \b\b", 6);
		quithandler();
		return ;
	}
	else if (c == SIGINT)
	{
		write(1, "\b\b  ", 4);
		sighandl();
		return ;
	}
}

//ctrl-c handler in child process

void	killchild(int signal)
{
	pid_t	*pid;

	(void)signal;
	pid = ft_return_global_pid();
	kill(*pid, SIGTERM);
}

//ctrl-\ handler in child process

void	quitchild(int signal)
{
	pid_t	*pid;

	(void)signal;
	pid = ft_return_global_pid();
	if (*pid != -1 && *pid > 0)
		kill(*pid, SIGTERM);
}
