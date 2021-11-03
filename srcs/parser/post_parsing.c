/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 20:19:12 by ogenser           #+#    #+#             */
/*   Updated: 2021/11/03 20:19:22 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	input_output_checker(t_mother *s)
{
	t_command	*cmd;
	int			in_out;
	int			cmd_index;

	cmd = s->c;
	cmd_index = 1;
	while (cmd != NULL)
	{
		in_out = cmd->isprecededbypipe + cmd->isprecededbyche
			+ cmd->isprecededbydoubleche;
		if (in_out > 1)
			input_corrector(s, cmd);
		in_out = cmd->isfollowedbypipe + cmd->isfollowedbyche
			+ cmd->isfollowedbydoubleche;
		if (in_out > 1)
			output_corrector(s, cmd);
		cmd = cmd->nextpipe;
		cmd_index++;
	}
}

void	input_corrector(t_mother *s, t_command *cmd)
{
	t_command	*temp;
	t_command	*next;

	if (cmd->isprecededbypipe && (cmd->isprecededbyche
			|| cmd->isprecededbydoubleche))
	{
		temp = s->c;
		next = NULL;
		while (temp != cmd)
		{
			if (temp->nextpipe != NULL)
				next = temp->nextpipe;
			free_one_cmd(s, temp);
			temp = next;
		}
		cmd->isprecededbypipe = 0;
		cmd->previouspipe = NULL;
		s->c = cmd;
	}
}

void	output_corrector(t_mother *s, t_command *cmd)
{
	t_command	*temp;
	t_command	*next;

	printf("ouptput corrected\n");
	if (cmd->isfollowedbypipe && (cmd->isfollowedbyche
			|| cmd->isfollowedbydoubleche))
	{
		temp = cmd->nextpipe;
		next = NULL;
		while (temp->nextpipe != NULL)
		{
			if (temp->nextpipe != NULL)
				next = temp->nextpipe;
			free_one_cmd(s, temp);
			temp = next;
		}
		free_one_cmd(s, temp);
		cmd->isfollowedbypipe = 0;
		cmd->nextpipe = NULL;
	}
}

int	ft_parse_error_detect(t_mother *s, int i)
{
	int		err;

	if (i == 1)
	{
		write(2, "Error, pipe or operator with no command\n", 40);
		s->ret = 1;
	}
	else if (i == 2)
	{
		s->ret = 2;
	}
	else if (i == 3)
	{
		write(2, "Minishell: commande introuvable\n", 32);
		s->ret = 127;
	}
	else if (i == 4)
	{
		write(2, "Error, weird input\n", 19);
		s->ret = 127;
	}
	err = 1;
	return (err);
}
