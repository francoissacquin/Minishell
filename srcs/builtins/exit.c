/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 17:22:56 by ogenser           #+#    #+#             */
/*   Updated: 2021/10/04 16:40:05 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//missing 
//find how to make the return of a command to a number
// export to superior level of shell so it's accessible after being exited with echo $?

long	ft_atol(char *str)
{
	int				i;
	long			count_sign;
	unsigned long	temp_ulong;
	long			final;

	count_sign = 1;
	i = 0;
	if (str[i] == '-')
	{
		count_sign = -1;
		i++;
	}
	temp_ulong = 0;
	while (str[i])
	{
		temp_ulong = temp_ulong * 10 + (str[i] - '0');
		i++;
		if (temp_ulong > 9223372036854775807 && count_sign == 1)
			return (2);
		else if (temp_ulong > 9223372036854775807 && count_sign  == -1)
			return (2);
	}
	final = count_sign * temp_ulong;
	return (final);
}

int	ft_check_exit_arg(char *str)
{
	int		i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (!(ft_isdigit(str[i])))
			return (1);
		if (i > 20)
			return (1);
		i++;
	}
	return (0);
}

int ft_exit(t_mother *s)
{
	long	temp;
	// if (s->c->isprecededbypipe != 0 && s->c->isfollowedbypipe == 0)
	// {
	// 	signal(SIGINT, signalhandler);
	// }
	// else if(s->c->isprecededbypipe != 0 && s->c->isfollowedbypipe != 0)
	// {
	// 	s->c = s->c->nextpipe;
	// 	multicommands(s);
	// }
	if (ft_strlen_array(s->c->arg) != 2)
		ft_error(s, "error\nwrong number of arguments for exit\n", 1);
	if (ft_check_exit_arg(s->c->arg[1]))
		s->ret = 2;
	temp  = ft_atol(s->c->arg[1]);
	if (temp < 0)
		temp = temp + (((temp / 256) + 1) * 256);
	else if (temp > 255)
		temp = temp - ((temp / 256) * 256);
	s->ret = temp;
	write(2, "exit\n", 5);
	// ft_end(s);
	// s->ret = 234;
	exit(s->ret);
}
