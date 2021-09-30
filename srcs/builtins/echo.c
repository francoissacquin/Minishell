/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 17:22:51 by ogenser           #+#    #+#             */
/*   Updated: 2021/09/04 11:47:43 by ogenser          ###   ########.fr       */
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

int	ft_echo(t_command *c)
{
	int		i;
	int		flag_n_switch;
	int ret = 1;

	i = 1;
	flag_n_switch = 0;
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
		ft_putstr_fd(c->arg[i], 1);
		i++;
	}
	if (flag_n_switch == 0)
		write(1, "\n", 1);
	
	return(ret);
}