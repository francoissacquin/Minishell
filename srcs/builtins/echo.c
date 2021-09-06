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

void	ft_echo(t_mother *s)
{
	char *toecho = "hello $USER caca";
	int	nflag = 1;
	int	dollar = 0;
	int i = 0;
	char *variable = "usr"; //viens du parsing

	while (i < (int)ft_strlen(toecho))
	{
		if (toecho[i] == '$')
		{
			ft_parserecho(s);
			dollar = 1;
		}
		i++;
	}
	i = 0;
	if (dollar == 1)
	{
		while(toecho[i] != '$' && i < (int)ft_strlen(toecho))
		{
			ft_putchar_fd(toecho[i], 1);
			i++;
		}
		while(toecho[i] != ' ' && i < (int)ft_strlen(toecho))
			i++;
		ft_putstr_fd(variable, 1);
		while(i < (int)ft_strlen(toecho))
		{
			ft_putchar_fd(toecho[i], 1);
			i++;
		}

	}
	else if (dollar == 0)
		ft_putstr_fd(toecho, 1);
	if (nflag == 0)
		ft_putchar_fd('\n', 1);
}