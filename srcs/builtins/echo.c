/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 17:22:51 by ogenser           #+#    #+#             */
/*   Updated: 2021/10/07 16:07:29 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// This is about to get absolutely bonkers so hold on tight :
// Because the c norm at 42 forbids more than 5 variables per function,
// We are using an int table to represent several variables in one.
// Here is the breakdown :
// idx[0]		i;
// idx[1]		j;
// idx[2]		increment_spaces;
// idx[3]		space_switch;
// idx[4]		flag_n_switch;
// idx[5]		quote_switch;

int	ft_echo(t_mother *s, t_command *c)
{
	int		ret;

	s->idx = ft_malloc(&s->idx, sizeof(int) * 6);
	s->idx[0] = 1;
	ret = 1;
	s->idx[4] = 0;
	if (c->arg[1] == NULL)
		ret = 0;
	if (c->arg[s->idx[0]] == NULL)
	{
		write(1, "\n", 1);
		return (ret);
	}
	echo_flag_skip(s, c);
	while (c->arg[s->idx[0]])
		echo_space_mega_loop(s, c);
	if (s->idx[4] == 0)
		write(1, "\n", 1);
	ret = 0;
	free(s->idx);
	return (ret);
}

void	echo_flag_skip(t_mother *s, t_command *c)
{
	while (c->arg[s->idx[0]] && !(ft_strcmp("-n", c->arg[s->idx[0]])))
	{
		s->idx[4] = 1;
		s->idx[0] = s->idx[0] + 1;
	}
}

void	echo_space_mega_loop(t_mother *s, t_command *c)
{
	if (!(ft_strcmp(c->arg[s->idx[0]], "$?")))
		ft_putnbr_fd(s->ret, 1);
	else
		ft_putstr_fd(c->arg[s->idx[0]], 1);
	s->idx[0] = s->idx[0] + 1;
	if (c->arg[s->idx[0]] != NULL)
		echo_space_medium_loop(s, c);
}

void	echo_space_medium_loop(t_mother *s, t_command *c)
{
	s->idx[1] = ft_strstr_index(s->line, "echo");
	s->idx[1] = s->idx[1] + 4;
	s->idx[1] = ft_skip_spaces(s->line, s->idx[1]);
	s->idx[2] = 1;
	s->idx[3] = 0;
	while (s->idx[2] < s->idx[0])
	{
		echo_space_inner_loop(s, c);
		s->idx[2] = s->idx[2] + 1;
	}
	if (c->arg[s->idx[0]][0] == '\0' && s->idx[5] == 0)
		s->idx[3] = 0;
	if (s->idx[3] == 1)
		ft_putstr_fd(" ", 1);
	s->idx[3] = 0;
}

void	echo_space_inner_loop(t_mother *s, t_command *c)
{
	(void)c;
	s->idx[5] = 0;
	if (s->line[s->idx[1]] == '\'' || s->line[s->idx[1]] == '\"')
		s->idx[1] = ft_skip_quote_marks(s->line, s->idx[1], ft_strlen(s->line));
	else
	{
		while (s->line[s->idx[1]] && s->line[s->idx[1]] != ' '
			&& s->line[s->idx[1]] != '\"' && s->line[s->idx[1]] != '\'')
			s->idx[1] = s->idx[1] + 1;
	}
	if (s->line[s->idx[1]] == ' ' && s->idx[2] + 1 == s->idx[0])
		s->idx[3] = 1;
	s->idx[1] = ft_skip_spaces(s->line, s->idx[1]);
	if (s->line[s->idx[1]] == '\'' || s->line[s->idx[1]] == '\"')
		s->idx[5] = 1;
}
