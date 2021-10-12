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


//on postule que la chaine arrive parsee aka debarasse de echo
// check for qotes simple and double

void ft_parserecho(t_mother *s)
{
	(void)s;
	// int simplequote = 0;
	// int doublequote = 0;


}

int		ft_skip_spaces(char *str, int i)
{
	while (str[i] == ' ')
		i++;
	return (i);
}

int	ft_echo(t_mother *s, t_command *c)
{
	int		i;
	int		j;
	int		increment_spaces;
	int		space_switch;
	int		flag_n_switch;
	int		quote_switch;
	int ret = 1;

	i = 1;
	flag_n_switch = 0;
	if(c->arg[1] == NULL)
		ret = 0;
	if (c->arg[i] == NULL)
	{
		write(1, "\n", 1);
		return (ret) ;
	}
	while (c->arg[i] && !(ft_strcmp("-n", c->arg[i])))
	{
		flag_n_switch = 1;
		i++;
	}
	while (c->arg[i])
	{
		if (!(ft_strcmp(c->arg[i], "$?")))
		{
			ft_putnbr_fd(s->ret, 1);
		}
		else
			ft_putstr_fd(c->arg[i], 1);
		i++;
		if (c->arg[i] != NULL)
		{
			j = ft_strstr_index(s->line, "echo");
			j = j + 4;
			j = ft_skip_spaces(s->line, j);
			increment_spaces = 1;
			space_switch = 0;
			while (increment_spaces < i)
			{
				quote_switch = 0;
				//printf("while i = %i, j = %i, space_switch = %i, increment_spaces = %i\n", i, j, space_switch, increment_spaces);
				if (s->line[j] == '\'' || s->line[j] == '\"')
					j = ft_skip_quote_marks(s->line, j, ft_strlen(s->line));
				else
				{
					while (s->line[j] && s->line[j] != ' ' && s->line[j] != '\"' && s->line[j] != '\'')
						j++;
				}
				if (s->line[j] == ' ' && increment_spaces + 1 == i)
					space_switch = 1;
				j = ft_skip_spaces(s->line, j);
				if (s->line[j] == '\'' || s->line[j] == '\"')
					quote_switch = 1;
				increment_spaces++;
			}
			//printf("i = %i, j = %i, space_switch = %i, increment_spaces = %i\n", i, j, space_switch, increment_spaces);
			if (c->arg[i][0] == '\0' && quote_switch == 0)
				space_switch = 0;
			if (space_switch == 1)
				ft_putstr_fd(" ", 1);
			space_switch = 0;
		}
	}
	if (flag_n_switch == 0)
		write(1, "\n", 1);
	ret = 0;
	return(ret);
}